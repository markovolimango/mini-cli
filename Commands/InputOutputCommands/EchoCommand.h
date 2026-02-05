#ifndef CLI_ECHOCOMMAND_H
#define CLI_ECHOCOMMAND_H

#include "IInputOutputCommand.h"

class EchoCommand : public IInputOutputCommand
{
public:
    explicit EchoCommand(std::shared_ptr<std::istream> in);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;
};


inline EchoCommand::EchoCommand(std::shared_ptr<std::istream> in) :
    IInputOutputCommand("echo")
{
    m_in = in;
}

#endif
