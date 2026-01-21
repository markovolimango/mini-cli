#ifndef CLI_LEXER_H
#define CLI_LEXER_H

#include <functional>
#include <vector>
#include <string>
#include "Token.h"

class Lexer
{
public:
    static std::vector<Token> tokenizeLine(const std::string& line);

private:
    static bool isWhitespace(char c);

    static std::string readUntil(const std::string& line, size_t& i, const std::function<bool(char)>& endCondition);
};


#endif
