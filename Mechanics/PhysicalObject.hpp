#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "../MathTools/Vector.hpp"
#include "../MathTools/Quaternion.hpp"

namespace Mechanics
{
    using namespace MathTools;

    class PhysicalObject
    {
        protected :

        // position and orientation of object in 3D space
        VectorD     position;
        QuaternionD orientation;

        public :

        VectorD get_position() const
        {
            return position;
        }

        QuaternionD get_orientation() const
        {
            return orientation;
        }
    };
}

#endif
