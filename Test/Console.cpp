#include "Console.hpp"

#include <iostream>
#include <string>

#include <stdlib.h>

namespace Test
{
    using namespace std;

    void Console::Clear()
    {
        system("clear");
    }

    void Console::Write(const char * line)
    {
        cout << line;
    }

    void Console::WriteLine()
    {
        cout << endl;
    }

    void Console::WriteLine(const char * line)
    {
        Console::Write(line);
        Console::WriteLine();
    }

    bool Console::ReadInt(int & result)
    {
        Console::Write("> ");

        string str;
        char c;

        while( (c = cin.get()) != '\n' )
        str += c;

        result = 0;
        const char * sz = str.c_str();

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
}
