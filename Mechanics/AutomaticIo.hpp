#ifndef AUTOMATICIO_HPP
#define AUTOMATICIO_HPP

namespace Mechanics
{
    template<typename T>
    struct AutomaticIo
    {
        T x, y;

        AutomaticIo operator+(AutomaticIo a)
        {
            AutomaticIo ret;

            ret.x = x + a.x;
            ret.y = y + a.y;

            return ret;
        }

        AutomaticIo operator-(AutomaticIo a)
        {
            AutomaticIo ret;

            ret.x = x - a.x;
            ret.y = y - a.y;

            return ret;
        }

        AutomaticIo operator*(AutomaticIo a)
        {
            AutomaticIo ret;

            ret.x = x * a.x;
            ret.y = y * a.y;

            return ret;
        }

        AutomaticIo operator/(AutomaticIo a)
        {
            AutomaticIo ret;

            ret.x = x / a.x;
            ret.y = y / a.y;

            return ret;
        }

        template<typename U, typename V>
        friend AutomaticIo<V> operator*(const U & a, const AutomaticIo<V> & b);

        template<typename U, typename V>
        friend AutomaticIo<V> operator*(const AutomaticIo<V> & b, const U & a);

        template<typename U, typename V>
        friend AutomaticIo<V> operator/(const U & a, const AutomaticIo<V> & b);

        template<typename U, typename V>
        friend AutomaticIo<V> operator/(const AutomaticIo<V> & b, const U & a);
    };

    template<typename U, typename V>
    AutomaticIo<V> operator*(const U & a, const AutomaticIo<V> & b)
    {
        AutomaticIo<V> ret;

        ret.x = a * b.x;
        ret.y = a * b.y;

        return ret;
    }

    template<typename U, typename V>
    AutomaticIo<V> operator*(const AutomaticIo<V> & b, const U & a)
    {
        return a * b;
    }

    template<typename U, typename V>
    AutomaticIo<V> operator/(const U & a, const AutomaticIo<V> & b)
    {
        AutomaticIo<V> ret;

        ret.x = a / b.x;
        ret.y = a / b.y;

        return ret;
    }

    template<typename U, typename V>
    AutomaticIo<V> operator/(const AutomaticIo<V> & b, const U & a)
    {
        AutomaticIo<V> ret;

        ret.x = b.x / a;
        ret.y = b.y / a;

        return ret;
    }
}

#endif
