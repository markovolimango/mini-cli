#include "TruncateFactory.h"
#include "../Commands/TruncateCommand.h"

static TruncateFactory g_truncateFactory;

std::unique_ptr<ICommand> TruncateFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Ivalid argument count");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("NIvalid argument type");

    return std::make_unique<TruncateCommand>(arguments[0].getText());
}
