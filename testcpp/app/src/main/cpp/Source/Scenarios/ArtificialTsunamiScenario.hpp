#include "Scenario.hpp"

namespace Scenarios {
  class ArtificialTsunamiScenario: public Scenario {
  private:
    /* data */
  public:
    ArtificialTsunamiScenario() = default;
    ~ArtificialTsunamiScenario() = default;

    RealType getWaterHeight(RealType x, RealType y) const override;
    RealType getBathymetry(RealType x, RealType y) const override;
    RealType getDisplacement(RealType x, RealType y) const override;
    RealType getBathymetryAfterEarthquake(RealType x, RealType y) const override; 
  };

} // namespace Scenarios