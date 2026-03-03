#include "TouchFactory.h"
#include "../Commands/TouchCommand.h"

static TouchFactory g_touchFactory;

std::unique_ptr<ICommand> TouchFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Invalid argument count");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Invalid argument type");

    return std::make_unique<TouchCommand>(arguments[0].getText());
}
