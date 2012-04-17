#ifndef SPACECRAFT_HPP
#define SPACECRAFT_HPP

#include "../Mechanics/PhysicalObject.hpp"
#include "../Mechanics/AutomaticSystem.hpp"
#include "../MathTools/GeometryTools.hpp"

#include <math.h>

namespace SpaceCraftMech
{
    using namespace Mechanics;

    class SpaceCraft : public PhysicalObject
    {
        // Translation model
        LinearAutomaticSystem<VectorD, 2, 0> tmodel;

        // Rotation model
        LinearAutomaticSystem<VectorD, 1, 0> rmodel;

        public :

        // Constructor
        // at : coefficients of the translation filter tmodel
        // ar : coefficients of the rotation filter rmodel
        SpaceCraft(double at[3], double speedMax, double ar[2], double angularSpeedMax);

        void Step(double delta, double rxCommand, double rzCommand, double throttle);
    };
}

#endif
