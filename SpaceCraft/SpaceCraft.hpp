#ifndef SPACECRAFT_HPP
#define SPACECRAFT_HPP

#include "../Mechanics/PhysicalObject.hpp"
#include "../Mechanics/AutomaticSystem.hpp"

namespace SpaceCraftMech
{
    using namespace Mechanics;

    const double bbuffer[1] = {1};

    class SpaceCraft : PhysicalObject
    {
        // Translation model
        LinearAutomaticSystem<VectorD, 2, 0> tmodel;

        // Rotation model
        LinearAutomaticSystem<VectorD, 2, 0> rmodel;

        public :

        SpaceCraft(double at[3], double ar[3]) :
            tmodel(at, bbuffer),
            rmodel(ar, bbuffer)
        {
        }
    };
}

#endif
