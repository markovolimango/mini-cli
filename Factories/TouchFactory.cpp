#include "TouchFactory.h"
#include "../Commands/TouchCommand.h"

std::unique_ptr<ICommand> TouchFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Nevalidan tip argumenta.");

    return std::make_unique<TouchCommand>(arguments[0].getText());
}
