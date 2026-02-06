#include "RMFactory.h"
#include "../Commands/RMCommand.h"

static RMFactory g_rmFactory;

std::unique_ptr<ICommand> RMFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Nevalidan tip argumenta.");

    return std::make_unique<RMCommand>(arguments[0].getText());
}
