#ifndef CONSOLE_HPP
#define CONSOLE_HPP

namespace Test
{
    class Console
    {
        public :

        static void Clear();

        static void Write(const char *);
        static void WriteLine();
        static void WriteLine(const char *);

        static bool ReadInt(int & );
    };
}

#endif
