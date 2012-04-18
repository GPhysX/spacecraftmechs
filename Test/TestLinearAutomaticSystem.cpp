#include "TestLinearAutomaticSystem.hpp"
#include "../Mechanics/AutomaticSystem.hpp"

#include <iostream>

namespace Test
{
    using namespace std;
    using namespace Mechanics;

    int TestLinearAutomaticSystem()
    {
        double a[] = {1, 1};
        double b[] = {1};

        cout << "Testing AutomaticSystem<double, 1, 0> :" << endl;
        LinearAutomaticSystem<double, 1, 0> system(a, b);

        return 0;
    }
}
