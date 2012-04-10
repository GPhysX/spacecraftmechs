#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "../MathTools/Quaternion.hpp"

namespace Mechanics
{
    using namespace MathTools;

    class PhysicalObject
    {
        // position and orientation of object in 3D space
        VectorD     position;
        QuaternionD orientation;
    };
}

#endif
