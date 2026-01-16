#ifndef CLI_ECHOCOMMAND_H
#define CLI_ECHOCOMMAND_H

#include "Command.h"

class EchoCommand : public Command
{
public:
    EchoCommand() = default;
    explicit EchoCommand(std::string text, bool isFilename);

    void execute(std::istream& in, std::ostream& out) override;

private:
    std::string m_filename;
    std::string m_string;

    static void echoStream(std::istream& in, std::ostream& out);
};

#endif
