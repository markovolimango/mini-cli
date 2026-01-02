#ifndef CLI_LEXER_H
#define CLI_LEXER_H

#include <vector>
#include <string>

struct Token
{
    std::string text;
    bool isQuoted;
};

class Lexer
{
public:
    static std::vector<Token> tokenize(const std::string& line);

private:
    static bool isWhitespace(char c);
};


#endif
