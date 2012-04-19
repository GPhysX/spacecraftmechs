#include "TestLinearAutomaticSystem.hpp"
#include "../Mechanics/AutomaticSystem.hpp"

#include "Console.hpp"

namespace Test
{
    using namespace std;
    using namespace Mechanics;

    int TestLinearAutomaticSystem()
    {
ChooseFormat :

        Console::WriteLine("Choose the output you want :");
        Console::WriteLine("[1] : csv file format");
        Console::WriteLine("[2] : Matlab variable");

        enum OutputFormat {CSV = 0, MFILE = 1};

        OutputFormat format;
        int n = 0;
        if(Console::ReadInt(n))
        {
            if(n == 1)
                format = CSV;
            else if(n == 2)
                format = MFILE;
            else
            {
                Console::WriteLine("Sorry, you might have entered an invalid choice");
                Console::Clear();
                goto ChooseFormat;
            }
        }

        Console::WriteLine();

ChooseFileName :

        return 0;
    }
}
