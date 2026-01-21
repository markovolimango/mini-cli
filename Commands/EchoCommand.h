#ifndef CLI_ECHOCOMMAND_H
#define CLI_ECHOCOMMAND_H

#include "Base/Command.h"

class EchoCommand : public InputOutputCommand
{
public:
    explicit EchoCommand(std::shared_ptr<std::istream> in);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;
};

#endif
