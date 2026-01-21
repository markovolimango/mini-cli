#include "Program/Program.h"
#include <iostream>

int main()
{
    Program::run(std::cin, std::cin, std::cout, std::cerr);
    return 0;
}
