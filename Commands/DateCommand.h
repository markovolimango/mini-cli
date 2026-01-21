#ifndef CLI_DATECOMMAND_H
#define CLI_DATECOMMAND_H

#include "Base/Command.h"

class DateCommand : public OutputCommand
{
public:
    explicit DateCommand();
    void execute(std::istream& inDefault, std::ostream& outDefault) override;
};
#endif
