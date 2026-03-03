#include "HeadFactory.h"
#include "../Commands/InputOutputCommands/HeadCommand.h"

static HeadFactory g_headFactory;

std::unique_ptr<ICommand> HeadFactory::create(const std::vector<Token>& arguments)
{
    int n;
    std::shared_ptr<std::istream> in = nullptr;

    if (!arguments.empty())
    {
        if (arguments[0].getType() != TokenType::Option)
            throw SyntaxError("Invalid argument type");
        if (arguments[0].getText()[0] != 'n')
            throw SyntaxError("Invalid argument");
        n = std::stoi(arguments[0].getText().substr(1));
    }
    if (arguments.size() > 1)
        in = createIn(arguments[1]);
    if (arguments.size() > 2)
        throw SyntaxError("Invalid argument count");

    return std::make_unique<HeadCommand>(n, in);
}
