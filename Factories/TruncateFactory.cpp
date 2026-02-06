#include "TruncateFactory.h"
#include "../Commands/TruncateCommand.h"

static TruncateFactory g_truncateFactory;

std::unique_ptr<ICommand> TruncateFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Nevalidan tip argumenta.");

    return std::make_unique<TruncateCommand>(arguments[0].getText());
}
