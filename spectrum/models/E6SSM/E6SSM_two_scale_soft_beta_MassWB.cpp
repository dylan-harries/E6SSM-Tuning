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

// File generated at Sun 15 Jun 2014 19:16:25

#include "E6SSM_two_scale_soft_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT soft_traces

/**
 * Calculates the one-loop beta function of MassWB.
 *
 * @return one-loop beta function
 */
double E6SSM_soft_parameters::calc_beta_MassWB_one_loop(const Soft_traces& soft_traces) const
{


   double beta_MassWB;

   beta_MassWB = 8*MassWB*oneOver16PiSqr*Sqr(g2);


   return beta_MassWB;
}

/**
 * Calculates the two-loop beta function of MassWB.
 *
 * @return two-loop beta function
 */
double E6SSM_soft_parameters::calc_beta_MassWB_two_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceLambda12AdjLambda12 =
      TRACE_STRUCT.traceLambda12AdjLambda12;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceAdjLambda12TLambda12 =
      TRACE_STRUCT.traceAdjLambda12TLambda12;


   double beta_MassWB;

   beta_MassWB = 0.4*twoLoop*Sqr(g2)*(10*traceAdjLambda12TLambda12 + 30*
      traceAdjYdTYd + 10*traceAdjYeTYe + 30*traceAdjYuTYu - 10*MassWB*
      traceLambda12AdjLambda12 - 30*MassWB*traceYdAdjYd - 10*MassWB*
      traceYeAdjYe - 30*MassWB*traceYuAdjYu + 18*MassB*Sqr(g1) + 18*MassWB*Sqr(
      g1) + 460*MassWB*Sqr(g2) + 120*MassG*Sqr(g3) + 120*MassWB*Sqr(g3) + 17*
      MassBp*Sqr(gN) + 17*MassWB*Sqr(gN) - 10*Conj(Lambdax)*(MassWB*Lambdax -
      TLambdax));


   return beta_MassWB;
}

} // namespace flexiblesusy
