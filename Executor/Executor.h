#ifndef CLI_EXECUTER_H
#define CLI_EXECUTER_H

#include "../Parsing/Parser.h"
#include <iostream>

class Executor
{
public:
    static void executePipeline(const Pipeline& pipeline, std::istream& inDefault, std::ostream& outDefault, std::ostream& err);
};

#endif
