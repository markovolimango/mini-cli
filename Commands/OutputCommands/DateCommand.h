#ifndef CLI_DATECOMMAND_H
#define CLI_DATECOMMAND_H

#include "IOutputCommand.h"

class DateCommand : public IOutputCommand
{
public:
    explicit DateCommand();
    void execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err) override;
};


inline DateCommand::DateCommand()
    : IOutputCommand("date")
{
}

#endif
