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

        void Step(double delta, VectorD tcommand, VectorD rcommand)
        {
            rcommand = Rotate(rcommand, this->orientation);

            VectorD rresult = rmodel.Step(delta, rcommand);

            double norm = sqrt(rresult.get_norm2());

            QuaternionD q(1, 0, 0, 0);

            if(norm > 0)
            {
                q = QuaternionD(cos(norm * delta),
                                sin(norm * delta) * rresult.get_x() / norm,
                                sin(norm * delta) * rresult.get_y() / norm,
                                sin(norm * delta) * rresult.get_z() / norm);
            }

            this->orientation = q * this->orientation;
            //this->orientation = (this->orientation /  sqrt(this->orientation.get_norm2())); compil error : WTF !!
        }
    };
}

#endif
