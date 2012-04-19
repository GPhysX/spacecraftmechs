#include "TestLinearAutomaticSystem.hpp"
#include "Console.hpp"

#include <map>

using namespace std;
using namespace Test;

int main()
{
    map<int, int(*)()> testMap;
    testMap[1] = TestLinearAutomaticSystem;

    Console::WriteLine("SpaceCraftMech");
    Console::WriteLine("Author : Guillaume BITTOUN");
    Console::WriteLine("");
    Console::WriteLine("Welcome to the Spacecraft test program.");

ReadTestNumber:

    Console::WriteLine("Please, choose your test :");
    Console::WriteLine("[1] : Automatic system test");

    int n = 0;
    if(Console::ReadInt(n) && testMap.find(n) != testMap.end() )
        testMap[n]();
    else
    {
        Console::Clear();
        Console::WriteLine("Sorry, you might have entered an invalid choice");
        Console::WriteLine();
        goto ReadTestNumber;
    }

    return 0;
}
