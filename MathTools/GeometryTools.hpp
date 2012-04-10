#ifndef GEOMETRYTOOLS_HPP
#define GEOMETRYTOOLS_HPP

#include "Vector.hpp"
#include "Quaternion.hpp"

namespace MathTools
{
    template<typename T, typename U>
    inline Vector<T> Rotate (const Vector<T> & v, const Quaternion<U> & q)
    {
        Quaternion<U> tmp(0, v.get_x(), v.get_y(), v.get_z());

        tmp = q * tmp * q.Conjugate();

        return Vector<T>(tmp.get_u(), tmp.get_v(), tmp.get_w());
    }
}

#endif
