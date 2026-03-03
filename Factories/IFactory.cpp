#include "IFactory.h"

std::shared_ptr<std::istream> IFactory::createIn(const Token& token)
{
    std::shared_ptr<std::istream> in = nullptr;
    if (token.getType() == TokenType::Normal)
    {
        in = std::make_shared<std::ifstream>(token.getText());
        if (!*in)
            throw OSError("Failed to open file");
    }
    else if (token.getType() == TokenType::Quoted)
        in = std::make_shared<std::istringstream>(token.getText());
    else
        throw SyntaxError("Invalid argument type");
    return in;
}
