#ifndef CLI_TIMECOMMAND_H
#define CLI_TIMECOMMAND_H

#include "IOutputCommand.h"

class TimeCommand : public IOutputCommand
{
public:
    explicit TimeCommand();
    void execute(std::istream& inDefault, std::ostream& outDefault) override;
};

inline TimeCommand::TimeCommand() :
    IOutputCommand("time")
{
}

#endif
