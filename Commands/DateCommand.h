#ifndef CLI_DATECOMMAND_H
#define CLI_DATECOMMAND_H

#include "Command.h"

class DateCommand : public Command
{
public:
    void execute(std::istream& in, std::ostream& out) override;
};


#endif
