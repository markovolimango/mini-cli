#include "RMFactory.h"
#include "../Commands/RMCommand.h"

static RMFactory g_rmFactory;

std::unique_ptr<ICommand> RMFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Invalid argument count");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Invalid argument type");

    return std::make_unique<RMCommand>(arguments[0].getText());
}
