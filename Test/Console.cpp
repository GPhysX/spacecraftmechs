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

    void Console::Write(const string & line)
    {
        cout << line;
    }

    void Console::WriteLine()
    {
        cout << endl;
    }

    void Console::WriteLine(const string & line)
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

    bool Console::ReadString(string & str)
    {
        Console::Write("> ");

        str = string();
        char c;

        while( (c = cin.get()) != '\n' )
            str += c;

        return true;
    }
}
