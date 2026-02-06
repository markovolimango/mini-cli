#include "TRFactory.h"
#include "../Commands/InputOutputCommands/TRCommand.h"

static TRFactory g_trFactory;

std::unique_ptr<ICommand> TRFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() == 1)
    {
        if (arguments[0].getType() != TokenType::OptionQuoted)
            throw SyntaxError("Nevalidan tip argumenta.");
        return std::make_unique<TRCommand>(nullptr, arguments[0].getText(), "");
    }
    if (arguments.size() == 2)
    {
        if (arguments[0].getType() == TokenType::OptionQuoted && arguments[1].getType() == TokenType::Quoted)
            return std::make_unique<TRCommand>(nullptr, arguments[0].getText(), arguments[1].getText());
        if ((arguments[0].getType() == TokenType::Normal || arguments[0].getType() == TokenType::Quoted) && arguments[1]
            .getType() == TokenType::OptionQuoted)
            return std::make_unique<TRCommand>(createIn(arguments[0]), arguments[1].getText(), "");
        throw SyntaxError("Nevalidan tip argumenta.");
    }
    if (arguments.size() == 3)
    {
        if ((arguments[0].getType() != TokenType::Normal && arguments[0].getType() != TokenType::Quoted) || arguments[1]
            .getType() != TokenType::OptionQuoted || arguments[2].getType() != TokenType::Quoted)
            throw SyntaxError("Nevalidan tip argumenta.");
        return std::make_unique<TRCommand>(createIn(arguments[0]), arguments[1].getText(), arguments[2].getText());
    }
    throw SyntaxError("Nevalidan broj argumenata.");
}
