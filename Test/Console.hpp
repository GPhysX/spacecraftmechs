#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

namespace Test
{
    using namespace std;

    class Console
    {
        public :

        static void Clear();

        static void Write(const string &);
        static void WriteLine();
        static void WriteLine(const string &);

        static bool ReadInt(int &);
        static bool ReadString(string &);
    };
}

#endif
