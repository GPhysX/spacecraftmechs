#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <iostream>

namespace MathTools
{
    using namespace std;

    // class Quaternion used to handle rotations
    template<typename T>
    class Quaternion
    {
        // factors a, u, v, w as Q = a + u*i + v*j + w*k
        T a, u, v, w;

        public :

        // constructors
        Quaternion() :
            a(0),
            u(0),
            v(0),
            w(0)
        {
        }

        Quaternion(T a, T u, T v, T w) :
            a(a),
            u(u),
            v(v),
            w(w)
        {
        }

        // get methods
        inline T get_a() const
        {
            return a;
        }

        inline T get_u() const
        {
            return u;
        }

        inline T get_v() const
        {
            return v;
        }

        inline T get_w() const
        {
            return w;
        }

        // norm computing
        inline T get_norm2() const
        {
            return sqrt(a*a + u*u + v*v + w*w);
        }

        // conjugate computing : Q* = a - u*i - v*j - w*k
        inline Quaternion Conjugate() const
        {
            return Quaternion(a, -u, -v, -w);
        }

        // Operators between Quaternions
        inline Quaternion & operator=(const Quaternion & x)
        {
            a = x.a;
            u = x.u;
            v = x.v;
            w = x.w;

            return *this;
        }

        template<typename U>
        friend Quaternion<U>   operator+ (const Quaternion<U> &, const Quaternion<U> &);

        template<typename U>
        friend Quaternion<U> & operator+=(Quaternion<U> &, const Quaternion<U> &);

        template<typename U>
        friend Quaternion<U>   operator- (const Quaternion<U> &, const Quaternion<U> &);

        template<typename U>
        friend Quaternion<U> & operator-=(Quaternion<U> &, const Quaternion<U> &);

        template<typename U>
        friend Quaternion<U>   operator* (const Quaternion<U> &, const Quaternion<U> &);

        template<typename U>
        friend Quaternion<U> & operator*=(Quaternion<U> &, const Quaternion<U> &);

        template<typename U, typename V>
        friend Quaternion<U>   operator/ (const Quaternion<U> &, const V &);

        template<typename U, typename V>
        friend Quaternion<U> & operator/=(Quaternion<U> &, const V &);

        template<typename U, typename V>
        friend Quaternion<U> operator* (const Quaternion<U> &, const V &);

        template<typename U, typename V>
        friend Quaternion<U> operator* (const V &, const Quaternion<U> &);

    };

    // base types for quaternion
    // These types would be preferred for SpaceCraft mechs computing
    typedef Quaternion<float > QuaternionF;
    typedef Quaternion<double> QuaternionD;

    const QuaternionD A(1, 0, 0, 0);
    const QuaternionD I(0, 1, 0, 0);
    const QuaternionD J(0, 0, 1, 0);
    const QuaternionD K(0, 0, 0, 1);

    // cout operator used to print Quaternion
    template<typename T>
    inline ostream & operator<< (ostream & o, const Quaternion<T> & q)
    {
        o << "Q{" << q.get_a() << ";" << q.get_u() << ";" << q.get_v() << ";" << q.get_w() << "}";

        return o;
    }

    // maths operators +*=
    template<typename T>
    inline Quaternion<T> operator+(const Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        return Quaternion<T>(
                             q1.a + q1.a,
                             q1.u + q2.u,
                             q1.v + q2.v,
                             q1.w + q2.w
                             );
    }

    template<typename T>
    inline Quaternion<T> & operator+=(Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        q1.a += q2.a;
        q1.u += q2.u;
        q1.v += q2.v;
        q1.w += q2.w;

        return q1;
    }

    template<typename T>
    inline Quaternion<T> operator-(const Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        return Quaternion<T>(
                             q1.a - q2.a,
                             q1.u - q2.u,
                             q1.v - q2.v,
                             q1.w - q2.w
                             );
    }

    template<typename T>
    inline Quaternion<T> & operator-=(Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        q1.a -= q2.a;
        q1.u -= q2.u;
        q1.v -= q2.v;
        q1.w -= q2.w;

        return q1;
    }

    template<typename T>
    inline Quaternion<T> operator*(const Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        Quaternion<T> ret(
                          q1.a * q2.a - q1.u * q2.u - q1.v * q2.v - q1.w * q2.w,
                          q1.a * q2.u + q1.u * q2.a + q1.v * q2.w - q1.w * q2.v,
                          q1.a * q2.v - q1.u * q2.w + q1.v * q2.a + q1.w * q2.u,
                          q1.a * q2.w + q1.u * q2.v - q1.v * q2.u + q1.w * q2.a
                          );

        return ret;
    }

    template<typename T>
    inline Quaternion<T> & operator*=(Quaternion<T> & q1, const Quaternion<T> & q2)
    {
        Quaternion<T> ret(
                          q1.a * q2.a - q1.u * q2.u - q1.v * q2.v - q1.w * q2.w,
                          q1.a * q2.u + q1.u * q2.a + q1.v * q2.w - q1.w * q2.v,
                          q1.a * q2.v - q1.u * q2.w + q1.v * q2.a + q1.w * q2.u,
                          q1.a * q2.w + q1.u * q2.v - q1.v * q2.u + q1.w * q2.a
                          );

        return (q1 = ret);
    }

    template<typename U, typename V>
    inline Quaternion<U>   operator/ (const Quaternion<U> & q, const V & x)
    {
        Quaternion<U> ret(
                          q.a / x,
                          q.u / x,
                          q.v / x,
                          q.w / x
                          );

        return ret;
    }

    template<typename U, typename V>
    inline Quaternion<U> & operator/=(Quaternion<U> & q, const V & x)
    {
        Quaternion<U> ret = q / x;

        return (q = ret);
    }

    template<typename U, typename V>
    inline Quaternion<U> operator* (const Quaternion<U> & q, const V & k)
    {
        return Quaternion<U>(q.a * k, q.u * k, q.v * k, q.w * k);
    }

    template<typename U, typename V>
    inline Quaternion<U> operator* (const V & k, const Quaternion<U> & q)
    {
        return q * k;
    }
}

#endif
