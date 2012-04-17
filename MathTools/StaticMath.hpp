#ifndef STATICMATH_HPP
#define STATICMATH_HPP

namespace MathTools
{
    template<bool> struct StaticCheck;
    template<> struct StaticCheck<true> {};

    template<int N>
    struct Log2: StaticCheck<((N & (N - 1)) == 0)>
    {
        enum {value = Log2<(N >> 1)>::value + 1 };
    };

    template<>
    struct Log2<1>
    {
        enum { value = 0 };
    };

        template<int N>
    struct SupPow2
    {
        static const int value = ((N & (N - 1)) == 0) ? (N << 1) : SupPow2<N - 1>::value;
    };

    template<>
    struct SupPow2<0>
    {
        static const int value = 1;
    };
}

#endif
