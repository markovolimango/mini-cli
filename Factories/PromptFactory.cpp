#include "PromptFactory.h"
#include "../Commands/PromptCommand.h"

static PromptFactory g_promptFactory;

std::unique_ptr<ICommand> PromptFactory::create(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Normal && arguments[0].getType() != TokenType::Quoted)
        throw SyntaxError("Nevalidan tip argumenta.");

    return std::make_unique<PromptCommand>(arguments[0].getText());
}
