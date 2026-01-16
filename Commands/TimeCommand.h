#ifndef CLI_TIMECOMMAND_H
#define CLI_TIMECOMMAND_H

#include "Command.h"

class TimeCommand : public Command
{
public:
    void execute(std::istream& in, std::ostream& out) override;
};

#endif
