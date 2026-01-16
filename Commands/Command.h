#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include "../Parsing/Argument.h"
#include <utility>
#include <vector>
#include <istream>
#include <ostream>

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(std::istream& in, std::ostream& out) = 0;
};
#endif //CLI_COMMAND_H
