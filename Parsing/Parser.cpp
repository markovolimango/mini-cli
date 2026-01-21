#include "Parser.h"
#include <fstream>
#include "../Errors/Errors.h"
#include "../Commands/Factory/CommandFactory.h"

Pipeline Parser::parseLine(const std::vector<Token>& tokens)
{
    size_t i = 0;
    Pipeline pipeline;

    while (i < tokens.size())
    {
        auto name = tokens[i++].getText();

        std::vector<Token> arguments;
        std::shared_ptr<std::istream> inRedirect = nullptr;
        std::shared_ptr<std::ostream> outRedirect = nullptr;
        while (i < tokens.size())
        {
            const auto& tok = tokens[i++];
            if (tok.getType() == TokenType::Pipe)
                break;
            if (tok.isArgument())
                arguments.push_back(tok);
            else if (tok.getType() == TokenType::InRedirect)
                inRedirect = std::make_shared<std::ifstream>(tok.getText());
            else if (tok.getType() == TokenType::OutRedirectTrunc)
                outRedirect = std::make_shared<std::ofstream>(tok.getText());
            else if (tok.getType() == TokenType::OutRedirectApp)
                outRedirect = std::make_shared<std::ofstream>(tok.getText(), std::ios::app);
        }

        pipeline.commandCalls.emplace_back(CommandFactory::createCommand(name, arguments), inRedirect, outRedirect);
    }

    return pipeline;
}
