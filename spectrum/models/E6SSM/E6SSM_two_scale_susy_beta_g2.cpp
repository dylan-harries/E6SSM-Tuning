// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Sun 15 Jun 2014 19:15:44

#include "E6SSM_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of g2.
 *
 * @return one-loop beta function
 */
double E6SSM_susy_parameters::calc_beta_g2_one_loop(const Susy_traces& susy_traces) const
{


   double beta_g2;

   beta_g2 = 4*Power(g2,3)*oneOver16PiSqr;


   return beta_g2;
}

/**
 * Calculates the two-loop beta function of g2.
 *
 * @return two-loop beta function
 */
double E6SSM_susy_parameters::calc_beta_g2_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceLambda12AdjLambda12 =
      TRACE_STRUCT.traceLambda12AdjLambda12;


   double beta_g2;

   beta_g2 = 0.2*Power(g2,3)*twoLoop*(-10*traceLambda12AdjLambda12 - 30*
      traceYdAdjYd - 10*traceYeAdjYe - 30*traceYuAdjYu - 10*AbsSqr(Lambdax) +
      18*Sqr(g1) + 230*Sqr(g2) + 120*Sqr(g3) + 17*Sqr(gN));


   return beta_g2;
}

} // namespace flexiblesusy
