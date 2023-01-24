//#include "TsunamiScenario.hpp"
//
//#include <algorithm>
//#include <cmath>
//#include <iostream>
//
//#define TOHOKU_BATH_X 3500
//#define TOHOKU_BATH_Y 2000
//#define TOHOKU_DISPL_X 250
//#define TOHOKU_DISPL_Y 400
//// path inside linux cluster
//#define FILE_PATH_TOHOKU_BATH "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/tohoku_2011/tohoku_gebco_ucsb3_2000m_hawaii_bath.nc"
//#define FILE_PATH_TOHOKU_DISPL "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/tohoku_2011/tohoku_gebco_ucsb3_2000m_hawaii_displ.nc"
//// path inside container
//// #define FILE_PATH_TOHOKU_BATH "/work/SWE/files/tohoku_2011/tohoku_gebco_ucsb3_2000m_hawaii_bath.nc"
//// #define FILE_PATH_TOHOKU_DISPL "/work/SWE/files/tohoku_2011/tohoku_gebco_ucsb3_2000m_hawaii_displ.nc"
//
//
//#define CHILE_BATH_X 7770
//#define CHILE_BATH_Y 5828
//#define CHILE_DISPL_X 555
//#define CHILE_DISPL_Y 555
//// path inside linux cluster
//#define FILE_PATH_CHILE_BATH "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/chile_2010/chile_gebco_usgs_2000m_bath.nc"
//#define FILE_PATH_CHILE_DISPL "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/chile_2010/chile_gebco_usgs_2000m_displ.nc"
//// path insider container
//// #define FILE_PATH_CHILE_BATH "/work/SWE/files/chile_2010/chile_gebco_usgs_2000m_bath.nc"
//// #define FILE_PATH_CHILE_DISPL "/work/SWE/files/chile_2010/chile_gebco_usgs_2000m_displ.nc"
//
//
//#define ARTI_BATH_X 1000
//#define ARTI_BATH_Y 1000
//#define ARTI_DISPL_X 100
//#define ARTI_DISPL_Y 100
//#define FILE_PATH_ARTI_BATH "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/artificialtsunami_bathymetry_1000.nc"
//#define FILE_PATH_ARTI_DISPL "/dss/dsshome1/lxc0E/t1221af/swe1d/SWE/files/artificialtsunami_displ_1000.nc"
//// path insider container
////#define FILE_PATH_ARTI_BATH "/work/SWE/files/artificialtsunami_bathymetry_1000.nc"
////#define FILE_PATH_ARTI_DISPL "/work/SWE/files/artificialtsunami_displ_1000.nc"
//
//#ifdef ENABLE_NETCDFENABLE_NETCDF
//
//NcFile tohoku_bath(FILE_PATH_TOHOKU_BATH, NcFile::ReadOnly);
//NcFile tohoku_displ(FILE_PATH_TOHOKU_DISPL, NcFile::ReadOnly);
//NcFile chile_bath(FILE_PATH_CHILE_BATH, NcFile::ReadOnly);
//NcFile chile_displ(FILE_PATH_CHILE_DISPL, NcFile::ReadOnly);
//NcFile arti_bath(FILE_PATH_ARTI_BATH, NcFile::ReadOnly);
//NcFile arti_displ(FILE_PATH_ARTI_DISPL, NcFile::ReadOnly);
//
//NcValues* values_tohokku_bath  = tohoku_bath.get_var(2)->values();
//NcValues* values_tohokku_displ = tohoku_displ.get_var(2)->values();
//NcValues* values_chile_bath    = chile_bath.get_var(2)->values();
//NcValues* values_chile_displ   = chile_displ.get_var(2)->values();
//NcValues* values_arti_bath     = arti_bath.get_var(2)->values();
//NcValues* values_arti_displ    = arti_displ.get_var(2)->values();
//
//// could be simplified
//RealType Scenarios::TsunamiScenario::getBathymetry(RealType x, RealType y) const {
//  if (x - (int)x != 0) {
//    x = (int)x;
//  }
//  if (y - (int)y != 0) {
//    y = (int)y;
//  }
//  // for tohoku
//  // RealType bath = RealType(values_tohokku_bath->as_float(y * TOHOKU_BATH_X + x));
//
//  // for chile
//  // RealType bath = RealType(values_chile_bath->as_float(y * CHILE_BATH_X + x));
//
//  // for artificial
//  RealType bath = RealType(values_arti_bath->as_float(y * ARTI_BATH_X + x));
//  return bath;
//}
//
//RealType Scenarios::TsunamiScenario::getBathymetryAfterEarthquake(RealType x, RealType y) const {
//  // for tohoku
//  //  y += 1150;
//  //  x += 150;
//
//  // // for chile
//  // x += 6660;
//  // y += 1100;
//
//  // for arti
//  // noting to add
//
//  RealType displ = RealType(0);
//  // for tohoku
//  // if (x < 375 && x > 125 && y < 1450 && y > 1050) {
//
//  // for chile
//  // if (x < 7215 && x > 6660 && y < 1655 && y > 1100) {
//  // for arti
//  if (x < 550 && x > 450 && y < 550 && y > 450) {
//    if (x - (int)x != 0) {
//      x = (int)x;
//    }
//    if (y - (int)y != 0) {
//      y = (int)y;
//    }
//    displ = getDisplacement(x, y) * 100;
//    // displ = getDisplacement(x, y);
//  }
//  return getBathymetry(x, y) + displ;
//}
//
//RealType Scenarios::TsunamiScenario::getWaterHeight(RealType x, RealType y) const {
//  // for tohoku
//  //  y += 1150;
//  //  x += 150;
//
//  // for chile
//  // x += 6660;
//  // y += 1100;
//
//  // for arti
//  // nothing to add
//
//  RealType h = -std::min(getBathymetry(x, y), RealType(0.0));
//  if(h != 100) {
//      // std::cout << "h != 100: h = " << h << " for x=" << x << ", y=" << y << std::endl;
//      // std::cout << "getBathymetry = " << getBathymetry(x,y) << std::endl;
//    }
//  return h;
//}
//
//RealType Scenarios::TsunamiScenario::getDisplacement(RealType x, RealType y) const {
//  // for tohoku
//  // RealType d = RealType(values_tohokku_displ->as_float((y - 1050) * TOHOKU_DISPL_X + (x - 125)));
//
//  // for chile
//  // RealType d = RealType(values_chile_displ->as_float((y - 1100) * CHILE_DISPL_X + (x - 6660)));
//
//  // for arti
//  RealType d = RealType(values_arti_displ->as_float((y - 450) * ARTI_DISPL_X + (x - 450)));
//
//  return d;
//}
//
//RealType Scenarios::TsunamiScenario::getBoundaryPos(BoundaryEdge edge) const {
//
//  // FOR CHILE
//  // if (edge == BoundaryEdge::Left) {
//  //   return RealType(-277);
//  // } else if (edge == BoundaryEdge::Right) {
//  //   return RealType(277);
//  // } else if (edge == BoundaryEdge::Bottom) {
//  //   return RealType(-277);
//  // } else {
//  //   return RealType(277);
//  // }
//
//  // FOR TOHOKU
//  //  if (edge == BoundaryEdge::Left) {
//  //    return RealType(-100);
//  //  } else if (edge == BoundaryEdge::Right) {
//  //    return RealType(100);
//  //  } else if (edge == BoundaryEdge::Bottom) {
//  //    return RealType(-100);
//  //  } else {
//  //    return RealType(100);
//  //  }
//
//  // FOR ARTI
//  if (edge == BoundaryEdge::Left) {
//    return RealType(-500);
//  } else if (edge == BoundaryEdge::Right) {
//    return RealType(500);
//  } else if (edge == BoundaryEdge::Bottom) {
//    return RealType(-500);
//  } else {
//    return RealType(500);
//  }
//}
//
//double Scenarios::TsunamiScenario::getEndSimulationTime() const { return double(0.1); }
//
//BoundaryType Scenarios::TsunamiScenario::getBoundaryType([[maybe_unused]] BoundaryEdge edge) const {
//  return BoundaryType::Outflow;
//}
//
//#endif
