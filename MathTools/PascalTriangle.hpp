#ifndef PASCALTRIANGLE_HPP
#define PASCALTRIANGLE_HPP

namespace MathTools
{
    template<int N>
    class PascalTriangle
    {
        int a[N][N];

        inline int ComputeValue(int n, int k)
        {
            if((n == k) || (k == 1))
                return a[n - 1][k - 1] = 1;
            else
                return (a[n - 1][k - 1] = ComputeValue(n - 1, k - 1) + ComputeValue(n - 1, k));
        }

        public :

        inline PascalTriangle() :
            a()
        {
            a[0][0] = a[1][0] = a[1][1] = 1;
            for(int i = 1 ; i <= N ; ++i)
                ComputeValue(N, i);
        }

        inline int Get(int n, int k)
        {
            return a[n-1][k-1];
        }
    };
}

#endif
