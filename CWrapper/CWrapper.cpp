#include "CWrapper.hpp"

#include "../MathTools/Vector.hpp"
#include "../SpaceCraft/SpaceCraft.hpp"

void * SpaceCraft_Create(double * at, double speedMax, double * ar, double angularSpeedMax)
{
    SpaceCraftMech::SpaceCraft * craft = new SpaceCraftMech::SpaceCraft(at, speedMax, ar, angularSpeedMax);

    return (void *)craft;
}

void SpaceCraft_Release(void * craft)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    delete craftPtr;
}

void SpaceCraft_Step(void * craft, double delta, double rxCommand, double rzCommand, double throttle)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    craftPtr->Step(delta, rxCommand, rzCommand, throttle);
}

struct Position SpaceCraft_GetPosition(void * craft)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    MathTools::VectorD position = craftPtr->get_position();

    struct Position Cposition;

    Cposition.x = position.get_x();
    Cposition.y = position.get_y();
    Cposition.z = position.get_z();

    return Cposition;
}

struct Orientation SpaceCraft_GetOrientation(void * craft)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    MathTools::QuaternionD orientation = craftPtr->get_orientation();

    struct Orientation Corientation;

    Corientation.a = orientation.get_a();
    Corientation.u = orientation.get_u();
    Corientation.v = orientation.get_v();
    Corientation.w = orientation.get_w();

    return Corientation;
}
