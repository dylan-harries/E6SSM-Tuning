// ====================================================================
// Class for calculating the fine tuning in the MSSM. Provides
// generic numerical routines as well as pMSSM-specific
// routines based on an analytical calculation.
// Notes:
//   - as of 26/8/2014, we currently only calculate fine tuning
//     neglecting family mixing (so stop matrix is simple 2x2)
// ====================================================================

#ifndef lowMSSM_TUNING_CALCULATOR_H
#define lowMSSM_TUNING_CALCULATOR_H

#include "lowMSSM_two_scale_model.hpp"
#include "lowMSSM_utilities.hpp"

#include "error.hpp"
#include "numerics.hpp"
#include <Eigen/Core>

namespace flexiblesusy {
   
   template <class T>
   class lowMSSM_tuning_calculator {
   public:
      lowMSSM_tuning_calculator()
         : model(0)
         , input_scale(0.)
         , tuning_scale(0.)
         , precision_goal(1.0e-4)
         , max_iterations(0)
         , tuning_loop_order(1) {}
      ~lowMSSM_tuning_calculator() {}

      double get_tuning_scale() const { return tuning_scale; }
      double get_input_scale()  const { return input_scale;  }
      const lowMSSM<Two_scale> &get_model() const { return model; }
      const Problems<lowMSSM_info::NUMBER_OF_PARTICLES> &get_problems() const {
         return model.get_problems();
      }
      int get_exit_code() const { return get_problems().have_serious_problem(); };
      void set_input_scale(double s) { input_scale = s; }
      void set_tuning_scale(double s) { tuning_scale = s; }
      void set_precision_goal(double precision_goal_) { precision_goal = precision_goal_; }
      void set_ewsb_loop_order(unsigned l) { model.set_ewsb_loop_order(l); }
      void set_tuning_loop_order(unsigned l) { tuning_loop_order = l; }
      void set_max_iterations(unsigned n) { max_iterations = n; }

   private:

      enum class stop_mass : char {mstop_1, mstop_2};

      lowMSSM<T> model;
      double input_scale, tuning_scale;
      double precision_goal; ///< precision goal
      unsigned max_iterations; ///< maximum number of iterations
      unsigned tuning_loop_order; ///< order of CW loop corrections included in tuning calculation (<= 1)
      /// For now, while just using stops, save the result for later use
      Eigen::Array<double, 2, 1> MStop;

      /// Helper methods in analytic tuning expressions.
      double gbar() const;
      double MFtop_DRbar() const;
      double stop_mass_matrix_LL_entry() const; ///< note LL = (0,0) entry
      double stop_mass_matrix_RR_entry() const; ///< note RR = (1,1) entry
      double stop_mass_matrix_LR_entry() const; ///< note LR = (0,1) entry
      double MQQ2() const;
      double RQQ() const;
      double stop_discriminant() const;

      void calculate_MStop();

      /// First derivatives of DR bar top mass - trivial, but useful to have
      /// for consistency with stop mass derivatives below.
      /// Makes use of parameters defined in lowMSSM_info
      double deriv_dMFtop2_dparam(lowMSSM_info::Parameters p) const;

      /// First derivatives of DR bar stop masses - these are the basic quantities
      /// entering into the simplified 1-loop tuning measures.
      double deriv_dMStop2_dvd(stop_mass which_stop) const;
      double deriv_dMStop2_dvu(stop_mass which_stop) const;
      double deriv_dMStop2_dmq222(stop_mass which_stop) const;
      double deriv_dMStop2_dmu222(stop_mass which_stop) const;
      double deriv_dMStop2_dMu(stop_mass which_stop) const;
      double deriv_dMStop2_dTYu22(stop_mass which_stop) const;
      double deriv_dMStop2_dparam(stop_mass which_stop, lowMSSM_info::Parameters p) const;

      /// Second derivatives of DR bar top mass
      double deriv_d2MFtop2_dparam_dparam(lowMSSM_info::Parameters p1, lowMSSM_info::Parameters p2) const; 

      /// Second derivatives of DR bar stop masses.
      double deriv_d2MStop2_dvd_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dvu_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dvd_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dMu_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dvd(stop_mass which_stop) const;
      double deriv_d2MStop2_dmq222_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dmu222_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dMu_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dTYu22_dvu(stop_mass which_stop) const;
      double deriv_d2MStop2_dparam_dparam(stop_mass which_stop, lowMSSM_info::Parameters p1, 
                                         lowMSSM_info::Parameters p2) const;

      /// Note a_0 has OPPOSITE sign convention to that used in cE6SSM paper,
      /// and therefore to that used in our expressions. Also A0 takes as input
      /// the mass, NOT the mass squared, and is evaluated at the current scale
      double deriv_d2DeltaV_dvd_dvd() const;
      double deriv_d2DeltaV_dvu_dvu() const;
      double deriv_d2DeltaV_dvu_dvd() const;
      double deriv_d2DeltaV_dmq222_dvd() const;
      double deriv_d2DeltaV_dmu222_dvd() const;
      double deriv_d2DeltaV_dMu_dvd() const;
      double deriv_d2DeltaV_dTYu22_dvd() const;
      double deriv_d2DeltaV_dmq222_dvu() const;
      double deriv_d2DeltaV_dmu222_dvu() const;
      double deriv_d2DeltaV_dMu_dvu() const;
      double deriv_d2DeltaV_dTYu22_dvu() const;

   };

} // namespace flexiblesusy

#endif