#include "BatchFactory.h"
#include "../Commands/OutputCommands/BatchCommand.h"

static BatchFactory g_batchFactory;

std::unique_ptr<ICommand> BatchFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Invalid argument count");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Invalid argument type");

    auto in = std::make_shared<std::ifstream>(arguments[0].getText());
    if (!*in)
        throw OSError("Failed to open file.");

    return std::make_unique<BatchCommand>(in);

    return nullptr;
}
