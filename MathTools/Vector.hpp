#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace MathTools
{
    using namespace std;

    template<typename T>
    class Vector
    {
        T x, y, z;

        public:

        // constructors
        Vector() :
            x(0),
            y(0),
            z(0)
        {
        }

        Vector(T x, T y, T z) :
            x(x),
            y(y),
            z(z)
        {
        }

        // accessors
        inline T get_x() const
        {
            return x;
        }

        inline T get_y() const
        {
            return y;
        }

        inline T get_z() const
        {
            return z;
        }

        // norm computing
        inline T get_norm2() const
        {
            return x*x + y*y + z*z;
        }

        // operators between vectors
        inline Vector & operator= (const Vector & v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        template<typename U>
        friend Vector<U>   operator+ (const Vector<U> &, const Vector<U> &);

        template<typename U>
        friend Vector<U> & operator+=(Vector<U> &, const Vector<U> &);

        template<typename U>
        friend Vector<U>   operator- (const Vector<U> &, const Vector<U> &);

        template<typename U>
        friend Vector<U> & operator-=(Vector<U> &, const Vector<U> &);

        // dot product declaration
        template<typename U>
        friend U           operator* (const Vector<U> &, const Vector<U> &);

        // cross product declaration
        template<typename U>
        friend Vector<U>   operator^ (const Vector<U> &, const Vector<U> &);

        template<typename U>
        friend Vector<U> & operator^=(Vector<U> &, const Vector<U> &);

        template<typename U, typename V>
        friend Vector<U>   operator/ (const Vector<U> & v, const V & x);

        template<typename U, typename V>
        friend Vector<U> & operator/=(const Vector<U> & v, const V & x);

        // scalar product
        template<typename U, typename V>
        friend Vector<U>   operator* (const V &, const Vector<U> &);

        template<typename U, typename V>
        friend Vector<U>   operator* (const Vector<U> &, const V &);
    };

    typedef Vector<float>  VectorF;
    typedef Vector<double> VectorD;

    const VectorD X(1, 0, 0);
    const VectorD Y(0, 1, 0);
    const VectorD Z(0, 0, 1);

    template<typename T>
    inline ostream & operator<< (ostream & o, const Vector<T> & v)
    {
        o << "V{" << v.get_x() << ";" << v.get_y() << ";" << v.get_z() << "}";

        return o;
    }

    template<typename U>
    inline Vector<U>   operator+ (const Vector<U> & v1, const Vector<U> & v2)
    {
        Vector<U> ret(
                         v1.x + v2.x,
                         v1.y + v2.y,
                         v1.z + v2.z
                         );

        return ret;
    }

    template<typename T>
    inline Vector<T> & operator+=(Vector<T> & v1, const Vector<T> & v2)
    {
        Vector<T> ret = v1 + v2;

        return (v1 = ret);
    }

    template<typename T>
    inline Vector<T>   operator- (const Vector<T> & v1, const Vector<T> & v2)
    {
        Vector<T> ret(
                         v1.x - v2.x,
                         v1.y - v2.y,
                         v1.z - v2.z
                         );

        return ret;
    }

    template<typename T>
    inline Vector<T> & operator-=(Vector<T> & v1, const Vector<T> & v2)
    {
        Vector<T> ret = v1 - v2;

        return (v1 = ret);
    }

    // dot product
    template<typename T>
    inline T operator* (const Vector<T> & v1, const Vector<T> & v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    // cross product
    template<typename T>
    inline Vector<T> operator^ (const Vector<T> & v1, const Vector<T> & v2)
    {
        Vector<T> ret(
                      v1.y * v2.z - v1.z * v2.y,
                      v1.z * v2.x - v1.x * v2.z,
                      v1.x * v2.y - v1.y * v2.x
                      );

        return ret;
    }

    template<typename T>
    inline Vector<T> operator^= (Vector<T> & v1, const Vector<T> & v2)
    {
        Vector<T> ret = v1 ^ v2;

        return (v1 = ret);
    }

    template<typename U, typename V>
    inline Vector<U> operator/  (const Vector<U> & v, const V & x)
    {
        Vector<U> ret(
                      v.x / x,
                      v.y / x,
                      v.z / x
                      );

        return ret;
    }

    template<typename U, typename V>
    inline Vector<U> & operator/= (Vector<U> & v, const V & x)
    {
        Vector<U> ret = v / x;

        return (v = ret);
    }

    template<typename U, typename V>
    inline Vector<U>   operator* (const V & k, const Vector<U> & v)
    {
        return Vector<U>(k * v.x, k*v.y, k*v.z);
    }

    template<typename U, typename V>
    inline Vector<U>   operator* (const Vector<U> & v, const V & k)
    {
        return k * v;
    }

    template<typename U, typename V>
    inline Vector<U> & operator*= (Vector<U> & v, const V & k)
    {
        return (v = (k * v));
    }
}

#endif
