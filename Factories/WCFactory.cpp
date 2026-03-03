#include "WCFactory.h"
#include "../Commands/InputOutputCommands/WCCommand.h"

static WCFactory g_wcFactory;

std::unique_ptr<ICommand> WCFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.empty() || arguments.size() > 2)
        throw SyntaxError("Ivalid argument count");

    if (arguments[0].getType() != TokenType::Option)
        throw SyntaxError("Ivalid argument type");

    bool countWords;
    if (arguments[0].getText() == "w")
        countWords = true;
    else if (arguments[0].getText() == "c")
        countWords = false;
    else
        throw SyntaxError("Invalid argument " + arguments[0].getText() + ".");

    std::shared_ptr<std::istream> in = nullptr;
    if (arguments.size() != 1)
        in = createIn(arguments[1]);
    return std::make_unique<WCCommand>(countWords, in);
}
