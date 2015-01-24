
/** 
   Project:     SOFTSUSY 
   File:        main.cpp
   Author:      Ben Allanach 
   Manual:      B.C. Allanach,hep-ph/0104145, Comp. Phys. Comm. 143 (2002) 305 
                B.C. Allanach, M.A. Bernhardt, arXiv:0903.1805, Comp. Phys. 
		Commun. 181 (2010) 232-245
   Webpage:     http://allanach.home.cern.ch/allanach/softsusy.html
   Description: main calling program example: performs a scan of tan beta 
   (starting at CMSSM10.1.1) and prints out Higgs masses as a result in
   the format
       <tan beta>      <mh0>     <mA0>    <mH0>     <mH+/->
*/

#include <iostream>
#include "softsusy_mycomplex.h"
#include "softsusy_def.h"
#include "softsusy_linalg.h"
#include "softsusy_lowe.h"
#include "softsusy_rge.h"
#include "softsusy_softsusy.h"
#include "softsusy_softpars.h"
#include "softsusy_susy.h"
#include "softsusy_utils.h"
#include "softsusy_numerics.h"

int main() {
  /// Sets up exception handling
  signal(SIGFPE, FPE_ExceptionHandler); 

  try {
 /// Sets format of output: 6 decimal places
  outputCharacteristics(6);

  cerr << "SOFTSUSY" << SOFTSUSY_VERSION 
       << " test program, Ben Allanach 2002\n";
  cerr << "If you use SOFTSUSY, please refer to B.C. Allanach,\n";
  cerr << "Comput. Phys. Commun. 143 (2002) 305, hep-ph/0104145\n";

  /// Parameters used: CMSSM parameters
  double m12 = 500., a0 = 0., mGutGuess = 2.0e16, tanb = 10.0, m0 = 125.;
  int sgnMu = 1;      ///< sign of mu parameter 
  int numPoints = 10; ///< number of scan points

  QedQcd oneset;      ///< See "lowe.h" for default definitions parameters

  /// most important Standard Model inputs: you may change these and recompile
  double alphasMZ = 0.1187, mtop = 173.5, mbmb = 4.18;
  oneset.setAlpha(ALPHAS, alphasMZ);
  oneset.setPoleMt(mtop);
  oneset.setMbMb(mbmb);

  oneset.toMz();      ///< Runs SM fermion masses to MZ

  /// Print out the SM data being used, as well as quark mixing assumption and
  /// the numerical accuracy of the solution
  cout << "# Low energy data in SOFTSUSY: MIXING=" << MIXING << " TOLERANCE=" 
       << TOLERANCE << endl << oneset << endl;

  /// Print out header line
  cout << "# tan beta   mh           mA           mH0          mH+-\n";

  int i; 
  /// Set limits of tan beta scan
  double startTanb = 3.0, endTanb = 50.0;
  /// Cycle through different points in the scan
  for (i = 0; i<=numPoints; i++) {

    tanb = (endTanb - startTanb) / double(numPoints) * double(i) +
      startTanb; // set tan beta ready for the scan.

    /// Preparation for calculation: set up object and input parameters
    MssmSoftsusy r; 
    DoubleVector pars(3); 
    pars(1) = m0; pars(2) = m12; pars(3) = a0;
    bool uni = true; // MGUT defined by g1(MGUT)=g2(MGUT)

    //DH:: added here
    numHiggsMassLoops = 1;
    numRewsbLoops = 1;    

    /// Calculate the spectrum
    r.lowOrg(sugraBcs, mGutGuess, pars, sgnMu, tanb, oneset, uni);

    /// check the point in question is problem free: if so print the output
    if (!r.displayProblem().test()) 
      cout << tanb << " " << r.displayPhys().mh0 << " " 
	   << r.displayPhys().mA0 << " " 
	   << r.displayPhys().mH0 << " " 
	   << r.displayPhys().mHpm << endl;
    else
      /// print out what the problem(s) is(are)
      cout << tanb << " " << r.displayProblem() << endl;
  }
  }
  catch(const string & a) { cout << a; return -1; }
  catch(const char * a) { cout << a; return -1; }
  catch(...) { cout << "Unknown type of exception caught.\n"; return -1; }

  return 0;
}