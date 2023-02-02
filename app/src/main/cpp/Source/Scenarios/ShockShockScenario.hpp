/**@file
 * */

#pragma once

#include "../Tools/RealType.hpp"

namespace Scenarios {
    class ShockShockScenario {
        const unsigned int size_;
        RealType h_; // heights of the left and the right wave respectively
        RealType hul_; // Momentum of the left wave as we can use its negative to find out the momentum of the right one

    public:
        ShockShockScenario(double h, double hu, unsigned int size);
        ~ShockShockScenario() = default;
        /**
         * @return Cell size of one cell (= domain size/number of cells)
         */
        RealType getCellSize() const;
        /**
         * @return Height of the left Wave
         */
        RealType getHeight();
        /**
         * @return Momentum of the Wave
         */
        RealType getMomentum(unsigned int pos);
}; // namespace Scenarios
}