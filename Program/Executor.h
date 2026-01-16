#ifndef CLI_EXECUTER_H
#define CLI_EXECUTER_H

#include "../Parsing/Parser.h"
#include <iostream>

class Executor
{
public:
    static void execute(const Pipeline& pipeline);
};

#endif
