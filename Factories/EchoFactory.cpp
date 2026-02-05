#include "EchoFactory.h"
#include "../Commands/InputOutputCommands/EchoCommand.h"

static EchoFactory g_echoFactory;

std::unique_ptr<ICommand> EchoFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() > 1)
        throw SyntaxError("Previse argumenata.");

    std::shared_ptr<std::istream> in = nullptr;
    if (arguments.size() == 1)
    {
        const auto& arg = arguments[0];
        if (arg.getType() == TokenType::Normal)
            in = std::make_shared<std::ifstream>(arg.getText());
        else if (arg.getType() == TokenType::Quoted)
            in = std::make_shared<std::istringstream>(arg.getText());
        else
            throw SyntaxError("Nevalidan tip argumenta.");
    }
    return std::make_unique<EchoCommand>(in);
}
