#include "TestLinearAutomaticSystem.hpp"
#include "../Mechanics/AutomaticSystem.hpp"

#include "Console.hpp"

#include <string>
#include <fstream>

namespace Test
{
    using namespace std;
    using namespace Mechanics;

    enum OutputFormat {CSV = 0, MFILE = 1};

    bool ReadOutputFormat(OutputFormat & format)
    {
        Console::WriteLine("Choose the output format :");
        Console::WriteLine("[1] : csv file format (*.csv)");
        Console::WriteLine("[2] : matlab file (*.m)");

        int n = 0;
        if(Console::ReadInt(n) && n == 1)
            format = CSV;
        else if(n == 2)
            format = MFILE;
        else
        {
            Console::WriteLine();
            Console::WriteLine("Sorry, you might have entered an invalid choice");
            return false;
        }

        return true;
    }

    bool ReadFileName(string & fileName)
    {
        Console::WriteLine("Choose the output file name (without extension) :");
        Console::ReadString(fileName);

        if(fileName.length() == 0)
        {
            Console::WriteLine("Sorry, filename size must be > 0");
            return false;
        }

        return true;
    }

    int TestLinearAutomaticSystem()
    {
        OutputFormat format;
        string fileName;
        fstream outputFile;

        Console::WriteLine();
        while(!ReadOutputFormat(format));

        Console::WriteLine();
        while(!ReadFileName(fileName));

        if(format == CSV)
            fileName += ".csv";
        else
            fileName += ".m";

        outputFile.open(fileName.c_str(), ios::out);

        outputFile.close();

        return 0;
    }
}
