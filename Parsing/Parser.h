#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include "Lexer.h"
#include "../Commands/ICommand.h"

struct CommandCall
{
    std::unique_ptr<ICommand> command;
    std::shared_ptr<std::istream> inRedirect;
    std::shared_ptr<std::ostream> outRedirect;

    CommandCall(std::unique_ptr<ICommand> command, std::shared_ptr<std::istream> inRedirect,
                std::shared_ptr<std::ostream> outRedirect);
};

struct Pipeline
{
    std::vector<CommandCall> commandCalls;
};

class Parser
{
public:
    static Pipeline parseLine(const std::vector<Token>& tokens);
};


inline CommandCall::CommandCall(std::unique_ptr<ICommand> command, std::shared_ptr<std::istream> inRedirect,
                                std::shared_ptr<std::ostream> outRedirect) :
    command(std::move(command)),
    inRedirect(inRedirect),
    outRedirect(outRedirect)
{
}

#endif
