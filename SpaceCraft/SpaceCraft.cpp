#include "SpaceCraft.hpp"

namespace SpaceCraftMech
{
    SpaceCraft::SpaceCraft(double at[3], double speedMax, double ar[2], double angularSpeedMax) :
        PhysicalObject(),
        tmodel(at, &speedMax),
        rmodel(ar, &angularSpeedMax)
    {
        orientation = QuaternionD(1, 0, 0, 0);
    }

    void SpaceCraft::Step(double delta, double rxCommand, double rzCommand, double throttle)
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
}

