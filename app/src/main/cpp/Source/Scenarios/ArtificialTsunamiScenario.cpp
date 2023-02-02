#include "ArtificialTsunamiScenario.hpp"
#include <algorithm>
#include <cmath>

RealType Scenarios::ArtificialTsunamiScenario::getBathymetry(RealType x, RealType y) const { return RealType(-100.0); }

RealType Scenarios::ArtificialTsunamiScenario::getWaterHeight(RealType x, RealType y) const {
  return RealType(100.0); // -(min Bathymetry)
}

RealType Scenarios::ArtificialTsunamiScenario::getDisplacement(RealType x, RealType y) const {
  RealType dx = RealType(std::sin(((x / 500) + 1) * M_PI));
  RealType dy = -std::pow((y / 500), 2) + 1;
  return 5 * dx * dy;
}

RealType Scenarios::ArtificialTsunamiScenario::getBathymetryAfterEarthquake(RealType x, RealType y) const{
  RealType displ = RealType(0.0);
  if(x > 450 && x < 550 && y > 450 && y < 550){
    displ = getDisplacement(x, y);
  }
  return getBathymetry(x, y) + displ;
}

RealType Scenarios::ArtificialTsunamiScenario::getBoundaryPos(BoundaryEdge edge) const {
  return 0;
}

BoundaryType Scenarios::ArtificialTsunamiScenario::getBoundaryType(BoundaryEdge edge) const {
  return Outflow;
}

double Scenarios::ArtificialTsunamiScenario::getEndSimulationTime() const {
  return 0;
}

