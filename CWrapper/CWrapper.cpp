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

void SpaceCraft_GetPosition(void * craft, struct Position * p)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    MathTools::VectorD position = craftPtr->get_position();

    p->x = position.get_x();
    p->y = position.get_y();
    p->z = position.get_z();
}

void SpaceCraft_GetOrientation(void * craft, struct Orientation * o)
{
    SpaceCraftMech::SpaceCraft * craftPtr = (SpaceCraftMech::SpaceCraft *)craft;

    MathTools::QuaternionD orientation = craftPtr->get_orientation();

    o->a = orientation.get_a();
    o->u = orientation.get_u();
    o->v = orientation.get_v();
    o->w = orientation.get_w();
}
