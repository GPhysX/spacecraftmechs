#ifndef SPACECRAFT_HPP
#define SPACECRAFT_HPP

#include "../Mechanics/PhysicalObject.hpp"
#include "../Mechanics/AutomaticSystem.hpp"
#include "../MathTools/GeometryTools.hpp"

#include <math.h>

namespace SpaceCraftMech
{
    using namespace Mechanics;

    const double bbuffer[1] = {1};

    class SpaceCraft : public PhysicalObject
    {
        // Translation model
        LinearAutomaticSystem<VectorD, 2, 0> tmodel;

        // Rotation model
        LinearAutomaticSystem<VectorD, 1, 0> rmodel;

        public :

        SpaceCraft(double at[3], double ar[2]) :
            tmodel(at, bbuffer),
            rmodel(ar, bbuffer)
        {
            orientation = QuaternionD(1, 0, 0, 0);
        }

        void Step(double delta, double rxCommand, double rzCommand, double throttle)
        {
            // Rotation computing
            VectorD vCommand = Rotate(VectorD(rxCommand, 0, rzCommand), this->orientation);

            VectorD result = rmodel.Step(delta, vCommand);

            double norm = sqrt(result.get_norm2());

            QuaternionD q(1, 0, 0, 0);

            if(norm > 0)
            {
                q = QuaternionD(cos(norm * delta),
                                sin(norm * delta) * result.get_x() / norm,
                                sin(norm * delta) * result.get_y() / norm,
                                sin(norm * delta) * result.get_z() / norm);
            }

            this->orientation = q * this->orientation;
            this->orientation = (this->orientation /  sqrt(this->orientation.get_norm2()));

            // Translation computing
            vCommand = Rotate(VectorD(0, 0, throttle), this->orientation);

            this->position = tmodel.Step(delta, vCommand);
        }
    };
}

#endif
