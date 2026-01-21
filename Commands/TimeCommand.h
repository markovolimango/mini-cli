#ifndef CLI_TIMECOMMAND_H
#define CLI_TIMECOMMAND_H

#include "Base/Command.h"

class TimeCommand : public OutputCommand
{
public:
    explicit TimeCommand();
    void execute(std::istream& inDefault, std::ostream& outDefault) override;
};

#endif
