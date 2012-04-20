#include "TestLinearAutomaticSystem.hpp"
#include "Console.hpp"

#include <map>

using namespace std;
using namespace Test;

bool ReadTestNumber(map<int, int(*)()> & testMap, int & n)
{
    Console::WriteLine("Please, choose your test :");
    Console::WriteLine("[1] : Automatic system test");

    if(Console::ReadInt(n) && testMap.find(n) != testMap.end() )
        return true;
    else
    {
        Console::WriteLine("Sorry, you might have entered an invalid choice");
        return false;
    }
}

int main()
{
    int testNumber;
    map<int, int(*)()> testMap;
    testMap[1] = TestLinearAutomaticSystem;

    Console::WriteLine("SpaceCraftMech");
    Console::WriteLine("Author : Guillaume BITTOUN");
    Console::WriteLine("");
    Console::WriteLine("Welcome to the Spacecraft test program.");

    Console::WriteLine();
    while(!ReadTestNumber(testMap, testNumber));

    testMap[testNumber]();

    return 0;
}
