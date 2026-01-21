#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include "Lexer.h"
#include "../Commands/Command.h"

struct CommandCall
{
    std::unique_ptr<Command> command;
    std::string inRedirect;
    std::string outRedirect;

    CommandCall(std::unique_ptr<Command> command, std::string inRedirect, std::string outRedirect);
};

struct Pipeline
{
    std::vector<CommandCall> commands;
};

class Parser
{
public:
    static Pipeline parseLine(const std::vector<Token>& tokens);
};


inline CommandCall::CommandCall(std::unique_ptr<Command> command, std::string inRedirect, std::string outRedirect) :
    command(std::move(command)),
    inRedirect(std::move(inRedirect)),
    outRedirect(std::move(outRedirect))
{
}

#endif
