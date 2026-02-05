#include "WCFactory.h"
#include "../Commands/InputOutputCommands/WCCommand.h"

static WCFactory g_wcFactory;

std::unique_ptr<ICommand> WCFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.empty() || arguments.size() > 2)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Option)
        throw SyntaxError("Nevalidan tip argumenta.");

    bool countWords;
    if (arguments[0].getText() == "-w")
        countWords = true;
    else if (arguments[0].getText() == "-c")
        countWords = false;
    else
        throw SyntaxError("Nevalidna opcija" + arguments[0].getText() + ".");

    std::shared_ptr<std::istream> in = nullptr;
    if (arguments.size() != 1)
    {
        const auto& arg = arguments[1];
        if (arg.getType() == TokenType::Normal)
            in = std::make_shared<std::ifstream>(arg.getText());
        else if (arg.getType() == TokenType::Quoted)
            in = std::make_shared<std::istringstream>(arg.getText());
        else
            throw SyntaxError("Nevalidan tip argumenta.");
    }
    return std::make_unique<WCCommand>(countWords, in);
}
