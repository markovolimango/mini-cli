#ifndef CLI_PROGRAM_H
#define CLI_PROGRAM_H
#include <istream>


class Program
{
public:
    static void run(std::istream& inCmd, std::istream& inData, std::ostream& out, std::ostream& err);
};


#endif
