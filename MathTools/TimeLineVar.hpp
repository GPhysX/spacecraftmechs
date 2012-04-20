#ifndef TIMELINEVAR_HPP
#define TIMELINEVAR_HPP

#include "StaticMath.hpp"

namespace MathTools
{
    /*
        The following buffer was implemented to optimize numerical recursion
        Buffer size must always be like 2^N-1
    */
    template<typename T, typename U, int O /*TimeLine order*/>
    class TimeLineVar
    {
        // buffers size
        static const int S = O - 1;

        T x[S];
        U y[S];

        public :

        TimeLineVar() :
            x(),
            y()
        {
            for(int i = 0 ; i < S ; ++i)
            {
                x[i] = T();
                y[i] = U();
            }
        }

        inline void Push(T delta, U yval)
        {
            for(int i = 0 ; i < S-1 ; ++i)
            {
                x[i] = x[i+1];
                y[i] = y[i+1];
            }

            x[S-1] = x[S-2] + delta;
            y[S-1] = yval;
        }

        inline U Get(T xval) const
        {
            int idxmin = -1, idxmax = -1;

            int idx  = O / 2 - 1;
            int next = O / 4;

            for(int i = 0 ; i < Log2<O>::value ; ++i)
            {
                if(xval < x[idx])
                {
                    idxmax = idx;
                    idx -= next;
                    next /= 2;
                }
                else if(xval > x[idx])
                {
                    idxmin = idx;
                    idx += next;
                    next /= 2;
                }
                else if(xval == x[idx])
                    return y[idx];
            }

            if(idxmax == -1)
                return y[idxmin];
            else if(idxmin == -1)
                return y[idxmax];

            return (y[idxmin]*(x[idxmax] - xval) + y[idxmax]*(xval - x[idxmin]) ) / (x[idxmax] - x[idxmin]);
        }

        inline void First(T & xval, U & yval)
        {
            xval = x[0];
            yval = y[0];
        }

        inline void Last (T & xval, U & yval)
        {
            xval = x[S-1];
            yval = y[S-1];
        }
    };
}

#endif
