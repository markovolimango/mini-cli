#include "EchoFactory.h"
#include "../Commands/InputOutputCommands/EchoCommand.h"

static EchoFactory g_echoFactory;

std::unique_ptr<ICommand> EchoFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() > 1)
        throw SyntaxError("Invalid argument count");

    std::shared_ptr<std::istream> in = nullptr;
    if (!arguments.empty())
        in = createIn(arguments[0]);
    return std::make_unique<EchoCommand>(in);
}
