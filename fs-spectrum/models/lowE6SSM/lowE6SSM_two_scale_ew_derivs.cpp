#include "lowE6SSM_two_scale_ew_derivs.hpp"

namespace flexiblesusy {
   lowE6SSM_ew_derivs::lowE6SSM_ew_derivs(const lowE6SSM<Two_scale>& m)
      : model(m)
      , number_of_ewsb_iterations(100)
      , ewsb_iteration_precision(1.0e-5)
   {
      double theta = 0.0;
      model.calculate_MSu_3rd_generation(MStop(0), MStop(1), theta);
      solve_ewsb_for_soft_masses();
   }

   void lowE6SSM_ew_derivs::set_ewsb_loop_order(unsigned l)
   {
      model.set_ewsb_loop_order(l);
      solve_ewsb_for_soft_masses();
   }

   void lowE6SSM_ew_derivs::set_model(const lowE6SSM<Two_scale>& m)
   {
      model = m;
      double theta = 0.0;
      model.calculate_MSu_3rd_generation(MStop(0), MStop(1), theta);
      solve_ewsb_for_soft_masses();
   }

   double lowE6SSM_ew_derivs::get_ewsb_condition_1() const
   {
      double result = model.get_ewsb_eq_hh_1();

      if (model.get_ewsb_loop_order() > 0) {
         result += deriv_dDeltaV_dparam(lowE6SSM_info::vd);
      }

      return result;
   }

   double lowE6SSM_ew_derivs::get_ewsb_condition_2() const
   {
      double result = model.get_ewsb_eq_hh_2();

      if (model.get_ewsb_loop_order() > 0) {
         result += deriv_dDeltaV_dparam(lowE6SSM_info::vu);
      }

      return result;
   }

   double lowE6SSM_ew_derivs::get_ewsb_condition_3() const
   {
      double result = model.get_ewsb_eq_hh_3();

      if (model.get_ewsb_loop_order() > 0) {
         result += deriv_dDeltaV_dparam(lowE6SSM_info::vs);
      }

      return result;
   }

   int lowE6SSM_ew_derivs::solve_ewsb_for_soft_masses()
   {
      int error = model.solve_ewsb_tree_level();

      if (error == 1)
         return error;

      if (model.get_ewsb_loop_order() > 0) {
         double mHd2 = model.get_mHd2();
         double mHu2 = model.get_mHu2();
         double ms2 = model.get_ms2();

         mHd2 -= deriv_dDeltaV_dparam(lowE6SSM_info::vd) / model.get_vd();
         mHu2 -= deriv_dDeltaV_dparam(lowE6SSM_info::vu) / model.get_vu();
         ms2 -= deriv_dDeltaV_dparam(lowE6SSM_info::vs) / model.get_vs();

         const bool is_finite = std::isfinite(mHu2) && std::isfinite(mHd2) 
            && std::isfinite(ms2);

         if (!is_finite) {
            error = 1;
         } else {
            model.set_mHd2(mHd2);
            model.set_mHu2(mHu2);
            model.set_ms2(ms2);
         }
      }

      return error;
   }

   Eigen::Matrix<double,3,3> lowE6SSM_ew_derivs::calculate_unrotated_mass_matrix_hh() const
   {
      Eigen::Matrix<double,3,3> mass_matrix(model.get_mass_matrix_hh());

      // Add in tadpole corrections
      if (model.get_ewsb_loop_order() > 0) {
         double d2DeltaV_dvd_dvd = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vd, lowE6SSM_info::vd);
         double d2DeltaV_dvd_dvu = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vd, lowE6SSM_info::vu);
         double d2DeltaV_dvd_dvs = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vd, lowE6SSM_info::vs);
         double d2DeltaV_dvu_dvu = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vu, lowE6SSM_info::vu);
         double d2DeltaV_dvu_dvs = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vu, lowE6SSM_info::vs);
         double d2DeltaV_dvs_dvs = deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::vs, lowE6SSM_info::vs);

         mass_matrix(0,0) += deriv_d2DeltaV_dvd_dvd;
         mass_matrix(0,1) += deriv_d2DeltaV_dvd_dvu;
         mass_matrix(0,2) += deriv_d2DeltaV_dvd_dvs;
         mass_matrix(1,0) += deriv_d2DeltaV_dvd_dvu;
         mass_matrix(1,1) += deriv_d2DeltaV_dvu_dvu;
         mass_matrix(1,2) += deriv_d2DeltaV_dvu_dvs;
         mass_matrix(2,0) += deriv_d2DeltaV_dvd_dvs;
         mass_matrix(2,1) += deriv_d2DeltaV_dvu_dvs;
         mass_matrix(2,2) += deriv_d2DeltaV_dvs_dvs;
      }

      return mass_matrix;
   }

   Eigen::Matrix<double,3,Eigen::Dynamic> lowE6SSM_ew_derivs::calculate_ewsb_parameter_derivs() const
   {

   }

   int lowE6SSM_ew_derivs::ewsb_conditions(const gsl_vector* x, void* params, gsl_vector* f)
      {
         if (contains_nan(x, number_of_eqsb_eqs)) {
            for (std::size_t i = 0; i < number_of_ewsb_eqs; ++i)
               gsl_vector_set(f, i, std::numeric_limits<double>::max());
            return GSL_EDOM;
         }

         const lowE6SSM_ew_derivs::Ewsb_vev_parameters* ewsb_params
            = static_cast<lowE6SSM_ew_derivs::Ewsb_vev_parameters*>(params);
         lowE6SSM_ew_derivs* derivs = ewsb_params->derivs;
         const std::size_t ewsb_loop_order = ewsb_params->ewsb_loop_order;

         double tadpole[number_of_ewsb_eqs];

         model->get_model().set_vd(gsl_vector_get(x, 0));
         model->get_model().set_vu(gsl_vector_get(x, 1));
         model->get_model().set_vs(gsl_vector_get(x, 2));

         tadpole[0] = model->get_model().get_ewsb_eq_hh_1();
         tadpole[1] = model->get_model().get_ewsb_eq_hh_2();
         tadpole[2] = model->get_model().get_ewsb_eq_hh_3();

         if (ewsb_loop_order > 0) {
            double msf1;
            double msf2;
            double theta;
            model->get_model.calculate_MSu_3rd_generation(msf1, msf2, theta);

            model->set_MStop(msf1, msf2);
            tadpole[0] += model->deriv_dDeltaV_dparam(lowE6SSM_info::vd);
            tadpole[1] += model->deriv_dDeltaV_dparam(lowE6SSM_info::vu);
            tadpole[2] += model->deriv_dDeltaV_dparam(lowE6SSM_info::vs);
         }

         for (std::size_t i = 0; i < number_of_ewsb_ews; ++i) 
            gsl_vector_set(f, i, tadpole[i]);

         return GSL_SUCCESS;
      }

   void lowE6SSM_ew_derivs::ewsb_initial_guess_for_vevs(double x_init[number_of_ewsb_eqs]) const
   {
      x_init[0] = model.get_vd();
      x_init[1] = model.get_vu();
      x_init[2] = model.get_vs();
   }

   int lowE6SSM_ew_derivs::solve_ewsb_for_vevs_iteratively_with(const gsl_multiroot_fsolver_type* solver,
                                                                const double x_init[number_of_ewsb_eqs])
   {
      Ewsb_vev_parameters params = {this, model.get_ewsb_loop_order()};
      Root_finder<number_of_ewsb_eqs> root_finder(lowE6SSM_ew_derivs::ewsb_conditions,
                                                  &params,
                                                  number_of_ewsb_iterations,
                                                  ewsb_iteration_precision);
      root_finder.set_solver_type(solver);
      const int status = root_finder.find_root(x_init);

      return status;
   }

   int lowE6SSM_ew_derivs::solve_ewsb_conditions_for_vevs()
   {
      const gsl_multiroot_fsolver_type* solvers[] = {
         gsl_multiroot_fsolver_hybrid,
         gsl_multiroot_fsolver_hyrbids,
         gsl_multiroot_fsolver_broyden,
         gsl_multiroot_fsolver_dnewton
      };

      double x_init[number_of_ewsb_eqs];
      ewsb_initial_guess_for_vevs(x_init);

#ifdef ENABLE_VERBOSE
      std::cout << "Solving EWSB equations ...\n"
         "\tInitial guess: x_init =";
      for (std::size_t i = 0; i < number_of_ewsb_eqs; ++i)
         std::cout << " " << x_init[i];
      std::cout << '\n';
#endif

      int status;
      for (std::size_t i = 0; i < sizeof(solvers)/sizeof(*solvers); ++i) {
         VERBOSE_MSG("\tStarting EWSB iteration using solver " << i);
         status = solve_ewsb_for_vevs_iteratively_with(solvers[i], x_init);
         if (status == GSL_SUCCESS) {
            VERBOSE_MSG("\tSolver " << i << " finished successfully!");
            break;
         }
#ifdef ENABLE_VERBOSE
         else {
            WARNING("\tSolver " << i << " could not find a solution!"
                    " (requested precision: " << ewsb_iteration_precision << ")");
         }
#endif
      }
      
      if (status != GSL_SUCCESS) {
         model.get_problems().flag_no_ewsb();
#ifdef ENABLE_VERBOSE
         WARNING("\tCould not find a solution to the EWSB equations!"
                 " (requested precision: " << ewsb_iteration_precision << ")");
#endif
      } else {
         model.get_problems().unflag_no_ewsb();
      }

      return status;
   }

   double lowE6SSM_ew_derivs::deriv_dDeltaV_dparam(lowE6SSM_info::Parameters p) const
   {
      double scale = model.get_scale();
      
      double dMStop20_dp = deriv_dMStop2_dparam(stop_mass::mstop_1, p);
      double dMStop21_dp = deriv_dMStop2_dparam(stop_mass::mstop_2, p);
      double dMFtop2_dp = deriv_dMFtop2_dparam(p);
      
      double mt = MFtop_DRbar();

      double a0_mstop1 = passarino_veltman::ReA0(Sqr(MStop(0)), Sqr(scale));
      double a0_mstop2 = passarino_veltman::ReA0(Sqr(MStop(1)), Sqr(scale));
      double a0_mtop = passarino_veltman::ReA0(Sqr(mt), Sqr(scale));

      double tmp_1 = -a0_mstop1 * dMStop20_dp;
      double tmp_2 = -a0_mstop2 * dMStop21_dp;
      double tmp_3 = 2.0 * a0_mtop * dMFtop2_dp;

      double result = 3.0 * oneOver16PiSqr * (tmp_1 + tmp_2 + tmp_3);

      return result;
   }

   double lowE6SSM_ew_derivs::deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::Parameters p1, lowE6SSM_info::Parameters p2) const
   {
      double scale = model.get_scale();

      double dMStop20_dp1 = deriv_dMStop2_dparam(stop_mass::mstop_1, p1);
      double dMStop20_dp2 = deriv_dMStop2_dparam(stop_mass::mstop_1, p2);
      double d2MStop20_dp1_dp2 = deriv_d2MStop2_dparam_dparam(stop_mass::mstop_1, p1, p2);

      double dMStop21_dp1 = deriv_dMStop2_dparam(stop_mass::mstop_2, p1);
      double dMStop21_dp2 = deriv_dMStop2_dparam(stop_mass::mstop_2, p2);
      double d2MStop21_dp1_dp2 = deriv_d2MStop2_dparam_dparam(stop_mass::mstop_2, p1, p2);

      double dMFtop2_dp1 = deriv_dMFtop2_dparam(p1);
      double dMFtop2_dp2 = deriv_dMFtop2_dparam(p2);
      double d2MFtop2_dp1_dp2 = deriv_d2MFtop2_dparam_dparam(p1, p2);

      double mt = MFtop_DRbar();

      double a0_mstop1 = passarino_veltman::ReA0(Sqr(MStop(0)), Sqr(scale));
      double a0_mstop2 = passarino_veltman::ReA0(Sqr(MStop(1)), Sqr(scale));
      double a0_mtop = passarino_veltman::ReA0(Sqr(mt), Sqr(scale));

      double tmp_1 = dMStop20_dp1 * dMStop20_dp2 * Log(Sqr(MStop(0) / scale));
      double tmp_2 = -a0_mstop1 * d2MStop20_dp1_dp2;
      double tmp_3 = dMStop21_dp1 * dMStop21_dp2 * Log(Sqr(MStop(1) / scale));
      double tmp_4 = -a0_mstop2 * d2MStop21_dp1_dp2;
      double tmp_5 = -2.0 * dMFtop2_dp1 * dMFtop2_dp2 * Log(Sqr(mt / scale));
      double tmp_6 = 2.0 * a0_mtop * d2MFtop2_dp1_dp2;

      double result = 3.0 * oneOver16PiSqr * (tmp_1 + tmp_2 + tmp_3 + tmp_4 + tmp_5 + tmp_6);

      return result;
   }

   bool lowE6SSM_ewsb_conditions::equal_as_unordered_pairs(lowE6SSM_info::Parameters p1, lowE6SSM_info::Parameters p2,
                                                          lowE6SSM_info::Parameters q1,lowE6SSM_info::Parameters q2) const
   {
      if ((p1 == q1 && p2 == q2) || (p1 == q2 && p2 == q1)) {
         return true;
      } else {
         return false;
      }
   }

   double lowE6SSM_ewsb_conditions::gbar() const
   {
      double g1  = model.get_g1();
      double g2  = model.get_g2();
      double thW = model.ThetaW();

      return (g2 * Cos(thW) + 0.7745966692414834 * g1 * Sin(thW));
   }

   double lowE6SSM_ewsb_conditions::MFtop_DRbar() const
   {
      double yt = model.get_Yu(2, 2);
      double vu = model.get_vu();

      return 0.7071067811865475 * yt * vu;
   }

} // namespace flexiblesusy
