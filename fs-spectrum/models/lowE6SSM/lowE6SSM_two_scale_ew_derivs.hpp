// ====================================================================
// Class for calculating derivatives of the EWSB conditions 
// in an E6 model.
// Notes:
//   - as of 26/8/2014, we currently only calculate fine tuning
//     neglecting family mixing (so stop matrix is simple 2x2)
//   - to fit in with our previous work, the fine tuning labelled
//     TLambdax is really that associated with the SUGRA parameter
//     ALambdax.
// ====================================================================

#ifndef lowE6SSM_EW_DERIVS_H
#define lowE6SSM_EW_DERIVS_H

#include "lowE6SSM_two_scale_model.hpp"

#include <Eigen/Core>
#include <utility>

namespace flexiblesusy {

   class lowE6SSM_ew_derivs {
   public:

      explicit lowE6SSM_ew_derivs(const lowE6SSM<Two_scale>&);

      double get_ewsb_loop_order() const { return model.get_ewsb_loop_order(); }
      void set_ewsb_loop_order(unsigned l);
      void set_model(const lowE6SSM<Two_scale>& m);
      void set_number_of_ewsb_iterations(std::size_t i) { number_of_ewsb_iterations = i; }
      void set_ewsb_iteration_precision(double p) { ewsb_iteration_precision = p; }

      lowE6SSM<Two_scale>& get_model() const { return model; }
      std::size_t get_number_of_ewsb_iterations() const { return number_of_ewsb_iterations; }
      double get_ewsb_iteration_precision() const { return ewsb_iteration_precision; }

      /// Values of EWSB conditions
      double get_ewsb_condition_1() const;
      double get_ewsb_condition_2() const;
      double get_ewsb_condition_3() const;

      /// Derivatives of EWSB conditions w.r.t VEVs
      Eigen::Matrix<double,3,3> calculate_unrotated_mass_matrix_hh() const;

      /// Derivatives of EWSB conditions w.r.t. model parameters
      Eigen::Matrix<double,3,Eigen::Dynamic> calculate_ewsb_parameter_derivs() const;

      /// Function to solve for VEVs given parameters
      int solve_ewsb_conditions_for_vevs();

      /// Derivatives of the Coleman-Weinbery loop contributions.
      /// By default only top and stop loops are included.
      double deriv_dDeltaV_dparam(lowE6SSM_info::Parameters p) const;
      double deriv_d2DeltaV_dparam_dparam(lowE6SSM_info::Parameters p1, lowE6SSM_info::Parameters p2) const;

   private:
      enum class stop_mass : char {mstop_1, mstop_2};

      static const std::size_t number_of_ewsb_eqs = 3;

      struct Ewsb_vev_parameters {
         lowE6SSM_ew_derivs derivs;
         std::size_t ewsb_loop_order;
      };

      lowE6SSM<Two_scale> model;
      std::size_t number_of_ewsb_iterations;
      double ewsb_iteration_precision;

      Eigen::Matrix<double,2,1> MStop;

      void set_MStop(double msf1, double msf2) { MStop(0) = msf1; MStop(1) = msf2; } 
      int ewsb_conditions(const gsl_vector* x, void* params, gsl_vector* f);
      int solve_ewsb_for_soft_masses();
      void ewsb_initial_guess_for_vevs(double x_init[number_of_ewsb_eqs]) const;

   int solve_ewsb_for_vevs_iteratively_with(const gsl_multiroot_fsolver_type* solver,
                                                                const double x_init[number_of_ewsb_eqs]);
      /// Useful for second derivatives
      bool equal_as_unordered_pairs(lowE6SSM_info::Parameters p1, lowE6SSM_info::Parameters p2,
                                    lowE6SSM_info::Parameters q1, lowE6SSM_info::Parameters q2) const;

      double gbar() const;
      double MFtop_DRbar() const;

      double stop_mass_matrix_LL_entry() const;
      double stop_mass_matrix_RR_entry() const;
      double stop_mass_matrix_LR_entry() const;

      double stop_MQQ2() const;
      double stop_RQQ() const;
      double stop_discriminant() const;

      double deriv_dMFtop2_dvu() const;
      double deriv_dMFtop2_dYu22() const;
      double deriv_d2MFtop2_dvu_dvu() const;
      double deriv_d2MFtop2_dYu22_dvu() const;
      double deriv_d2MFtop2_dYu22_dYu22() const;

      double deriv_dMStop2_dvd(stop_mass which_stop) const;
      double deriv_dMStop2_dvu(stop_mass which_stop) const;
      double deriv_dMStop2_dvs(stop_mass which_stop) const;
      double deriv_dMStop2_dg1(stop_mass which_stop) const;
      double deriv_dMStop2_dg2(stop_mass which_stop) const;
      double deriv_dMStop2_dgN(stop_mass which_stop) const;
      double deriv_dMStop2_dYu22(stop_mass which_stop) const;
      double deriv_dMStop2_dmq222(stop_mass which_stop) const;
      double deriv_dMStop2_mu222(stop_mass which_stop) const;
      double deriv_dMStop2_dLambdax(stop_mass which_stop) const;
      double deriv_dMStop2_dTYu22(stop_mass which_stop) const;

      double deriv_dMStop2_dparam(stop_mass which_stop, lowE6SSM_info::Parameters p) const;

      double deriv_d2MStop2_dvd_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dvd_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dvd_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dg1_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dg2_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dvu_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dvu_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dg1_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dg2_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dvs_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dg1_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dg2_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dvs(stop_mass which_stop) const;
      double deriv_d2MStop2_dg1_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dg2_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dg1(stop_mass which_stop) const;
      double deriv_d2MStop2_dg2_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dg2(stop_mass which_stop) const;
      double deriv_d2MStop2_dgN_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dgN(stop_mass which_stop) const;
      double deriv_d2MStop2_dYu22_dYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dmq222(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dmq222(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dmq222(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dmq222(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dmu222(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dmu222(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dmu222(stop_mass which_stop) const;
      double deriv_d2MStop2_dLambdax_dLambdax(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dLambdax(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dTYu22(stop_mass which_stop) const;
      double deriv_d2MStop2_dparam_dparam(stop_mass which_stop, lowE6SSM_info::Parameters p1, lowE6SSM_info::Parameters p2) const;

   };

} // namespace flexiblesusy

#endif
