#include "Test/TestLinearAutomaticSystem.hpp"

#include <iostream>
#include <map>

using namespace std;
using namespace Test;

bool IntParse(const char * sz, int & result)
{
    result = 0;

    while(*sz != 0)
    {
        if(*sz < 48 || *sz > 57)
            return false;

        result *= 10;
        result += (*sz - 48);

        ++sz;
    }

    return true;
}

int main()
{
    map<int, int(*)()> testMap;
    testMap[1] = TestLinearAutomaticSystem;

    cout << "SpaceCraftMech" << endl;
    cout << "Author : Guillaume BITTOUN" << endl;
    cout << endl;
    cout << "Welcome to the Spacecraft test program." << endl;

ReadTestNumber:

    cout << "Please, choose your test :" << endl;
    cout << "[1] : Automatic system test" << endl;
    cout << "> ";

    string str;
    char c;

    while( (c = cin.get()) != '\n' )
        str += c;

    int n = 0;
    if(IntParse(str.c_str(), n) && testMap.find(n) != testMap.end() )
        testMap[n]();
    else
    {
        cout << endl << "Sorry, you might have entered an invalid number" << endl << endl;
        goto ReadTestNumber;
    }

    return 0;
}
