#include "Scenario.hpp"

#ifdef ENABLE_NETCDF
#include </usr/include/netcdfcpp.h>
#endif

namespace Scenarios {

  class TsunamiScenario: public Scenario {
  private:
    /* data */
  public:
    TsunamiScenario()  = default;
    ~TsunamiScenario() = default;

    /**
     *
     *
     * @param x the x coordinate
     * @param y the y coordinate
     * @return water height before the earthquake
     * */
    RealType     getWaterHeight(RealType x, RealType y) const override;
      /**
      *
      *
      * @param x the x coordinate
      * @param y the y coordinate
      * @return bathymetry before the earthquake
      * */
    RealType     getBathymetry(RealType x, RealType y) const override;
      /**
        *
        *
        * @param x the x coordinate
        * @param y the y coordinate
        * @return diplacement after the earthquake
        * */
    RealType     getDisplacement(RealType x, RealType y) const override;

      /**
       * @param edge is what edge you are asking for
       * @return coordinate of whatever edge is being asked
       * */
    RealType     getBoundaryPos(BoundaryEdge edge) const override;

      /**
        * @param edge is what edge you are asking about
        * @return the boundary type
        * */
    BoundaryType getBoundaryType([[maybe_unused]] BoundaryEdge edge) const override;

      /**
       *
       *
       * @param x the x coordinate
       * @param y the y coordinate
       * @return bathymetry after the earthquake
       * */
    //RealType getBathymetryAfterEarthquake(RealType x, RealType y) const override;

      /**
        * @return how long the simulation is supposed to run for
        * */
    double getEndSimulationTime() const override;
    // double getEndSimulationTime() const;
  };

} // namespace Scenarios
