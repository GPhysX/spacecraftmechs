#ifndef MODULATOR_HPP
#define MODULATOR_HPP

class Modulator
{
    double a, b;

    public :

    Modulator()
    {
        a = 1.0;
        b = 0.0;
    }

    inline void set_a(double a)
    {
        this->a = a;
    }

    inline void set_b(double b)
    {
        this->b = b;
    }

    inline void Set(double a, double b)
    {
        this->a = a;
        this->b = b;
    }

    inline void Reset()
    {
        a = 1.0;
        b = 0.0;
    }

    inline double Modulate(double x)
    {
        return a * x + b;
    }
};

#endif
