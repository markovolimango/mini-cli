#include "Parser.h"
#include <fstream>
#include "../Errors/Error.h"
#include "../Factories/Registry.h"
#include "../Factories/IFactory.h"

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
            if (tok.getType() == TokenType::Operator && tok.getText() == "|")
                break;
            if (tok.isArgument())
                arguments.push_back(tok);
            else if (tok.getType() == TokenType::Operator && tok.getText() == "<")
            {
                if (i >= tokens.size())
                    throw SyntaxError("Empty redirection");
                inRedirect = std::make_shared<std::ifstream>(tokens[i++].getText());
            }
            else if (tok.getType() == TokenType::Operator && tok.getText() == ">")
            {
                if (i >= tokens.size())
                    throw SyntaxError("Empty redirection");
                outRedirect = std::make_shared<std::ofstream>(tokens[i++].getText());
            }
            else if (tok.getType() == TokenType::Operator && tok.getText() == ">>")
            {
                if (i >= tokens.size())
                    throw SyntaxError("Empty redirection");
                outRedirect = std::make_shared<std::ofstream>(tokens[i++].getText(), std::ios::app);
            }
        }

        auto command = std::move(Registry::getFactory(name)->create(arguments));

        pipeline.commandCalls.emplace_back(std::move(command), inRedirect, outRedirect);
    }

    return pipeline;
}
