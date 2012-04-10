#include "MathTools/Vector.hpp"
#include "MathTools/Quaternion.hpp"
#include "Mechanics/AutomaticSystem.hpp"

#include <windows.h>
#include <math.h>

using namespace MathTools;

int test_Quaternion()
{
    QuaternionD a(1,1,1,1);

    cout << a * I << " " << I * a << " " << I * I << endl;

    return 0;
}

int test_Vector()
{
    VectorD v1(1,1,1), v2(0,1,1);

    cout << v1 * v2 << " " << (v1 ^ v2) << endl;

    return 0;
}

int test_Pascal()
{
    PascalTriangle<20> p;

    int sum = 0;

    DWORD t0 = GetTickCount();

    for(int iter = 0 ; iter < 10000 ; ++iter)
    {
        for(int i = 1 ; i <= 10 ; ++i)
        {
            for(int j = 1 ; j <= i ; ++j)
            {
                sum += p.Get(i, j);
            }
        }
    }

    DWORD t1 = GetTickCount();

    cout << t1 - t0 << endl;

    cout << sum << endl << endl;

    for(int i = 1 ; i <= 10 ; ++i)
    {
        for(int j = 1 ; j <= i ; ++j)
        {
            cout << p.Get(i, j) << endl;
        }

        cout << endl;
    }


    return 0;
}

using namespace Mechanics;

#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int test_filterVector()
{
    srand(time(0));

    double coeffa[4] = {0, 1, 1, 1};
    double coeffb[1] = {1};

    LinearAutomaticSystem<VectorD, 3, 0> a(coeffa, coeffb);

    fstream f("caca.csv", ios::out);

    double accu = 0;
    VectorD command;

    for(int i = 0 ; i < 10000 ; ++i)
    {
        double timeStep = 0.02 + 0.01 * (2.0 * rand() / ((double)RAND_MAX) - 1);
        accu += timeStep;

        if(accu < 50)
            command = VectorD(10., 5.0, 2.0);
        else
            command = VectorD(0., 0.5, .0);

        VectorD result = a.Step(timeStep, command);

        f << accu << ";" <<  result.get_x() << ";" << result.get_y() << ";" << result.get_z() << endl;
    }

    f.close();

    return 0;
}

bool isNaN(const VectorD & v)
{
    return isnan(v.get_x()) || isnan(v.get_y()) || isnan(v.get_z());
}

QuaternionD Ln(const QuaternionD & q)
{
    VectorD v(q.get_u(), q.get_v(), q.get_w());

    double a = log(q.get_norm2()) / 2;

    double v_coeff = q.get_a() / (sqrt(q.get_norm2()));
    v_coeff = acos(v_coeff);
    v_coeff /= sqrt(v.get_norm2());

    if(isnan(v_coeff))
    {
        return QuaternionD(a, 0, 0, 0);
    }

    v *= v_coeff;

    return QuaternionD(a, v.get_x(), v.get_y(), v.get_z());
}

QuaternionD Exp(const QuaternionD & q)
{
    double exp_a = exp(q.get_a());

    VectorD v(q.get_u(), q.get_v(), q.get_w());

    double vnorm = sqrt(v.get_norm2());
    double inv_vnorm = 1 / vnorm;

    double a = exp_a*cos(vnorm);

    if(isnan(inv_vnorm) || isinf(inv_vnorm))
    {
        return QuaternionD(a, 0, 0, 0);
    }

    v *= (inv_vnorm * sin(vnorm));

    return QuaternionD(a, v.get_x(), v.get_y(), v.get_z());
}

#include "MathTools/GeometryTools.hpp"

int main()
{
    double coeffa[3] = {1, 1, 1};
    double coeffb[1] = {1};

    LinearAutomaticSystem<VectorD, 2, 0> a(coeffa, coeffb);

    fstream f("caca.csv", ios::out);

    double accu = 0;
    VectorD command;

    QuaternionD orientation(1, 0, 0, 0);

    const double delta = 2 * M_PI / 20;

    for(int i = 0 ; i < 10000 ; ++i)
    {
        double timeStep = 0.02 + 0.01 * (2.0 * rand() / ((double)RAND_MAX) - 1);
        accu += timeStep;

        if(accu < 40)
            command = Rotate(VectorD(0, delta, 0), orientation);
        else if(accu < 80)
            command = Rotate(VectorD(0, 0, delta), orientation);
        else
            command = VectorD(0, 0, 0);

        VectorD result = a.Step(timeStep, command);

        double norm = sqrt(result.get_norm2());

        QuaternionD q(1, 0, 0, 0);

        if(norm > 0)
        {
            result /= norm;
            norm *= timeStep;
            q = QuaternionD(cos(norm), sin(norm) * result.get_x(), sin(norm) * result.get_y(), sin(norm) * result.get_z());
        }

        orientation = q * orientation;

        VectorD v = Rotate(VectorD(0, 1, 0), orientation);

        f << accu << ";" << v.get_x() << ";" << v.get_y() << ";" << v.get_z() << endl;
        //f << accu << ";" <<  q.get_a() << ";" << q.get_u() << ";" << q.get_v() << ";" << q.get_w() << endl;
        //f << accu << ";" <<  orientation.get_a() << ";" << orientation.get_u() << ";" << orientation.get_v() << ";" << orientation.get_w() << endl;
    }

    f.close();

    return 0;
}
