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

// File generated at Sun 15 Jun 2014 19:18:03

#include "E6SSM_physical.hpp"

#include <iostream>

namespace flexiblesusy {

E6SSM_physical::E6SSM_physical()
   :
    MVG(0), MGlu(0), MFv(Eigen::Array<double,3,1>::Zero()), MChaP(0), MVP(0),
       MVZ(0), MVZp(0), MSd(Eigen::Array<double,6,1>::Zero()), MSv(Eigen::Array<
       double,3,1>::Zero()), MSu(Eigen::Array<double,6,1>::Zero()), MSe(
       Eigen::Array<double,6,1>::Zero()), MSDX(Eigen::Array<double,6,1>::Zero()),
       Mhh(Eigen::Array<double,3,1>::Zero()), MAh(Eigen::Array<double,3,1>::Zero()
       ), MHpm(Eigen::Array<double,2,1>::Zero()), MChi(Eigen::Array<double,6,1>
       ::Zero()), MCha(Eigen::Array<double,2,1>::Zero()), MFe(Eigen::Array<double,
       3,1>::Zero()), MFd(Eigen::Array<double,3,1>::Zero()), MFu(Eigen::Array<
       double,3,1>::Zero()), MFDX(Eigen::Array<double,3,1>::Zero()), MSHI0(
       Eigen::Array<double,4,1>::Zero()), MSHIp(Eigen::Array<double,4,1>::Zero()),
       MChaI(Eigen::Array<double,2,1>::Zero()), MChiI(Eigen::Array<double,4,1>
       ::Zero()), MSSI0(Eigen::Array<double,2,1>::Zero()), MFSI(Eigen::Array<
       double,2,1>::Zero()), MSHp0(Eigen::Array<double,2,1>::Zero()), MSHpp(
       Eigen::Array<double,2,1>::Zero()), MChiP(Eigen::Array<double,2,1>::Zero()),
       MVWm(0)

   , ZD(Eigen::Matrix<double,6,6>::Zero()), ZV(Eigen::Matrix<double,3,3>::Zero(
      )), ZU(Eigen::Matrix<double,6,6>::Zero()), ZE(Eigen::Matrix<double,6,6>
      ::Zero()), ZDX(Eigen::Matrix<double,6,6>::Zero()), ZH(Eigen::Matrix<double,3
      ,3>::Zero()), ZA(Eigen::Matrix<double,3,3>::Zero()), ZP(Eigen::Matrix<double
      ,2,2>::Zero()), ZN(Eigen::Matrix<std::complex<double>,6,6>::Zero()), UM(
      Eigen::Matrix<std::complex<double>,2,2>::Zero()), UP(Eigen::Matrix<
      std::complex<double>,2,2>::Zero()), ZEL(Eigen::Matrix<std::complex<double>,3
      ,3>::Zero()), ZER(Eigen::Matrix<std::complex<double>,3,3>::Zero()), ZDL(
      Eigen::Matrix<std::complex<double>,3,3>::Zero()), ZDR(Eigen::Matrix<
      std::complex<double>,3,3>::Zero()), ZUL(Eigen::Matrix<std::complex<double>,3
      ,3>::Zero()), ZUR(Eigen::Matrix<std::complex<double>,3,3>::Zero()), ZDXL(
      Eigen::Matrix<std::complex<double>,3,3>::Zero()), ZDXR(Eigen::Matrix<
      std::complex<double>,3,3>::Zero()), UHI0(Eigen::Matrix<double,4,4>::Zero()),
      UHIp(Eigen::Matrix<double,4,4>::Zero()), ZMI(Eigen::Matrix<std::complex<
      double>,2,2>::Zero()), ZPI(Eigen::Matrix<std::complex<double>,2,2>::Zero()),
      ZNI(Eigen::Matrix<std::complex<double>,4,4>::Zero()), ZSSI(Eigen::Matrix<
      double,2,2>::Zero()), ZFSI(Eigen::Matrix<std::complex<double>,2,2>::Zero()),
      UHp0(Eigen::Matrix<double,2,2>::Zero()), UHpp(Eigen::Matrix<double,2,2>
      ::Zero()), ZNp(Eigen::Matrix<std::complex<double>,2,2>::Zero())

{
}

void E6SSM_physical::clear()
{
   MVG = 0.0;
   MGlu = 0.0;
   MFv = Eigen::Array<double,3,1>::Zero();
   MChaP = 0.0;
   MVP = 0.0;
   MVZ = 0.0;
   MVZp = 0.0;
   MSd = Eigen::Array<double,6,1>::Zero();
   ZD = Eigen::Matrix<double,6,6>::Zero();
   MSv = Eigen::Array<double,3,1>::Zero();
   ZV = Eigen::Matrix<double,3,3>::Zero();
   MSu = Eigen::Array<double,6,1>::Zero();
   ZU = Eigen::Matrix<double,6,6>::Zero();
   MSe = Eigen::Array<double,6,1>::Zero();
   ZE = Eigen::Matrix<double,6,6>::Zero();
   MSDX = Eigen::Array<double,6,1>::Zero();
   ZDX = Eigen::Matrix<double,6,6>::Zero();
   Mhh = Eigen::Array<double,3,1>::Zero();
   ZH = Eigen::Matrix<double,3,3>::Zero();
   MAh = Eigen::Array<double,3,1>::Zero();
   ZA = Eigen::Matrix<double,3,3>::Zero();
   MHpm = Eigen::Array<double,2,1>::Zero();
   ZP = Eigen::Matrix<double,2,2>::Zero();
   MChi = Eigen::Array<double,6,1>::Zero();
   ZN = Eigen::Matrix<std::complex<double>,6,6>::Zero();
   MCha = Eigen::Array<double,2,1>::Zero();
   UM = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   UP = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MFe = Eigen::Array<double,3,1>::Zero();
   ZEL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZER = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFd = Eigen::Array<double,3,1>::Zero();
   ZDL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZDR = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFu = Eigen::Array<double,3,1>::Zero();
   ZUL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZUR = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFDX = Eigen::Array<double,3,1>::Zero();
   ZDXL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZDXR = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MSHI0 = Eigen::Array<double,4,1>::Zero();
   UHI0 = Eigen::Matrix<double,4,4>::Zero();
   MSHIp = Eigen::Array<double,4,1>::Zero();
   UHIp = Eigen::Matrix<double,4,4>::Zero();
   MChaI = Eigen::Array<double,2,1>::Zero();
   ZMI = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   ZPI = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MChiI = Eigen::Array<double,4,1>::Zero();
   ZNI = Eigen::Matrix<std::complex<double>,4,4>::Zero();
   MSSI0 = Eigen::Array<double,2,1>::Zero();
   ZSSI = Eigen::Matrix<double,2,2>::Zero();
   MFSI = Eigen::Array<double,2,1>::Zero();
   ZFSI = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MSHp0 = Eigen::Array<double,2,1>::Zero();
   UHp0 = Eigen::Matrix<double,2,2>::Zero();
   MSHpp = Eigen::Array<double,2,1>::Zero();
   UHpp = Eigen::Matrix<double,2,2>::Zero();
   MChiP = Eigen::Array<double,2,1>::Zero();
   ZNp = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MVWm = 0.0;

}

void E6SSM_physical::print(std::ostream& ostr) const
{
   ostr << "----------------------------------------\n"
           "one-loop pole masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MGlu = " << MGlu << '\n';
   ostr << "MFv = " << MFv.transpose() << '\n';
   ostr << "MChaP = " << MChaP << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';
   ostr << "MVZp = " << MVZp << '\n';
   ostr << "MSd = " << MSd.transpose() << '\n';
   ostr << "MSv = " << MSv.transpose() << '\n';
   ostr << "MSu = " << MSu.transpose() << '\n';
   ostr << "MSe = " << MSe.transpose() << '\n';
   ostr << "MSDX = " << MSDX.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHpm = " << MHpm.transpose() << '\n';
   ostr << "MChi = " << MChi.transpose() << '\n';
   ostr << "MCha = " << MCha.transpose() << '\n';
   ostr << "MFe = " << MFe.transpose() << '\n';
   ostr << "MFd = " << MFd.transpose() << '\n';
   ostr << "MFu = " << MFu.transpose() << '\n';
   ostr << "MFDX = " << MFDX.transpose() << '\n';
   ostr << "MSHI0 = " << MSHI0.transpose() << '\n';
   ostr << "MSHIp = " << MSHIp.transpose() << '\n';
   ostr << "MChaI = " << MChaI.transpose() << '\n';
   ostr << "MChiI = " << MChiI.transpose() << '\n';
   ostr << "MSSI0 = " << MSSI0.transpose() << '\n';
   ostr << "MFSI = " << MFSI.transpose() << '\n';
   ostr << "MSHp0 = " << MSHp0.transpose() << '\n';
   ostr << "MSHpp = " << MSHpp.transpose() << '\n';
   ostr << "MChiP = " << MChiP.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';

   ostr << "----------------------------------------\n"
           "one-loop pole mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZD = " << ZD << '\n';
   ostr << "ZV = " << ZV << '\n';
   ostr << "ZU = " << ZU << '\n';
   ostr << "ZE = " << ZE << '\n';
   ostr << "ZDX = " << ZDX << '\n';
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "ZN = " << ZN << '\n';
   ostr << "UM = " << UM << '\n';
   ostr << "UP = " << UP << '\n';
   ostr << "ZEL = " << ZEL << '\n';
   ostr << "ZER = " << ZER << '\n';
   ostr << "ZDL = " << ZDL << '\n';
   ostr << "ZDR = " << ZDR << '\n';
   ostr << "ZUL = " << ZUL << '\n';
   ostr << "ZUR = " << ZUR << '\n';
   ostr << "ZDXL = " << ZDXL << '\n';
   ostr << "ZDXR = " << ZDXR << '\n';
   ostr << "UHI0 = " << UHI0 << '\n';
   ostr << "UHIp = " << UHIp << '\n';
   ostr << "ZMI = " << ZMI << '\n';
   ostr << "ZPI = " << ZPI << '\n';
   ostr << "ZNI = " << ZNI << '\n';
   ostr << "ZSSI = " << ZSSI << '\n';
   ostr << "ZFSI = " << ZFSI << '\n';
   ostr << "UHp0 = " << UHp0 << '\n';
   ostr << "UHpp = " << UHpp << '\n';
   ostr << "ZNp = " << ZNp << '\n';

}

std::ostream& operator<<(std::ostream& ostr, const E6SSM_physical& phys_pars)
{
   phys_pars.print(std::cout);
   return ostr;
}

} // namespace flexiblesusy
