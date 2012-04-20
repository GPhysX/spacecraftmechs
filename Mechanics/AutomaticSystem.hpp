#ifndef AUTOMATICSYSTEM_HPP
#define AUTOMATICSYSTEM_HPP

#include "../MathTools/TimeLineVar.hpp"
#include "../MathTools/PascalTriangle.hpp"
#include "AutomaticIo.hpp"
#include "Modulator.hpp"

namespace Mechanics
{
    using namespace MathTools;

    /*
    This object is used to process an automatic system like :

        sigma(a(k+1)*y(n-k), k={0..N}) = sigma(b(k+1)*x(n-k), k={0..M})

    This is a simple filter used to simulate a linear mechanical system.
    It can be used with Quaternion and Vector to handle both rotation and translation mechanic

    NX and NY are the size of vectors X and Y used to compute the next step of Y
    */
    template<typename U, int OY = 0 /*filter order on Y*/, int OX = 0 /*filter order on X*/>
    class LinearAutomaticSystem
    {
        static const int SX = OX + 1;
        static const int SY = OY + 1;

        enum BufferType {XBUFFER, YBUFFER};

        double a[SY];
        double b[SX];

        Modulator a_mod[SY];
        Modulator b_mod[SX];

        TimeLineVar<double, AutomaticIo<U>, SupPow2< (SX > SY ? SX : SY) >::value > xysamples;

        PascalTriangle< (SX > SY ? SX : SY) > pTriangle;

        inline void FillPrevious(U * x_previous, U* y_previous, double delta)
        {
            double last_t;
            AutomaticIo<U> last_u;

            // Retrieves the last time computed
            xysamples.Last(last_t, last_u);

            for(int i = 1 ; i < (SX > SY ? SX : SY) ; ++i)
            {
                AutomaticIo<U> element = xysamples.Get(last_t - (i - 1) * delta);

                if(i < SX)
                    x_previous[i] = element.x;
                if(i < SY)
                    y_previous[i] = element.y;
            }
        }

        template<BufferType T>
        inline U ComputeSampleBuffer(U * previous, double delta)
        {
            int offsetMin = 0, offsetMax = 0;
            double invTe = 1, invDelta = 1 / delta;

            double    * coeffs     = (T == XBUFFER) ? b     : a;
            Modulator * mod_coeffs = (T == XBUFFER) ? b_mod : a_mod;

            U result = U();

            for(int i = 0 ; i < (T == XBUFFER ? SX : SY) ; i++)
            {
                int sign = 1;

                for(int j = -offsetMin, count = 1 ; j <= offsetMax ; ++j, ++count)
                {
                    double coeff = mod_coeffs[i].Modulate((*(coeffs + i)));
                    result += (coeff * previous[(T == XBUFFER ? (SX-1)/2 : (SY-1)/2) + j] * sign * pTriangle.Get(i+1, count)) * invTe;
                    sign = -sign;
                }

                (i % 2 ? ++offsetMin : ++offsetMax);

                invTe *= invDelta;
            }

            return result;
        }

        inline void PushFinalResult(U x, U y, double delta)
        {
            AutomaticIo<U> result;
            result.x = x;
            result.y = y;

            xysamples.Push(delta, result);
        }

        inline double ComputeLastFactor(double delta)
        {
            double te_pow = 1, factor = 0;

            for(int i = 0 ; i < OY ; ++i)
            {
                if( (OY % 2) && (i == OY - 1) )
                    factor += (a[SY - 2] / te_pow);

                te_pow *= delta;
            }

            factor += (a[SY - 1] / te_pow);

            return 1 / factor;
        }

        public :

        LinearAutomaticSystem()
        {
            for(int i = 1 ; i < SY - 1 ; ++i)
                a[i] = 0;
            a[SY - 1] = 1;

            for(int i = 1 ; i < SX - 1 ; ++i)
                b[i] = 0;
            b[SX - 1] = 1;
        }

        LinearAutomaticSystem(const double a_in[SY], const double b_in[SX])
        {
            for(int i = 0 ; i < SY ; ++i)
                a[i] = a_in[i];

            for(int i = 0 ; i < SX ; ++i)
                b[i] = b_in[i];
        }

        inline U Step(double delta, U xnew)
        {
            U x_previous[SX];
            U y_previous[SY];

            // Setting values for x(n-0) and y(n-0)
            // y(n-0) is the value we're computing but it's set to 0 to not interfere in the computing
            x_previous[0] = xnew;
            y_previous[0] = U();

            // Fill x_previous and y_previous buffers
            FillPrevious(x_previous, y_previous, delta);

            // Computes result of recursion :
            // sigma(b(k)*x(n-k), k=0..K) - sigma(a(k)*y(n-k), k=1..K)
            // rhr => Right-hand result
            U rhr = ComputeSampleBuffer<XBUFFER>(x_previous, delta) - ComputeSampleBuffer<YBUFFER>(y_previous, delta);

            // Computes the Te^n
            double factor = ComputeLastFactor(delta);

            U result = rhr * factor;

            PushFinalResult(xnew, result, delta);

            return result;
        }

        template<BufferType T, int N>
        inline void SetModulator(double a, double b)
        {
            if(T == XBUFFER)
                a_mod[N].Set(a, b);
            else if(T == YBUFFER)
                b_mod[N].Set(a, b);
        }
    };
}

#endif
