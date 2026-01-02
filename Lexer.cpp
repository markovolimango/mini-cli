#include "Lexer.h"
#include "errors/Errors.h"

std::vector<Token> Lexer::tokenize(const std::string& line)
{
    size_t i = 0;
    std::vector<Token> tokens;

    while (true)
    {
        while (i < line.length() && isWhitespace(line[i]))
            i++;
        if (i >= line.length())
            break;

        if (line[i] == '"')
        {
            std::string text;
            i++;
            while (i < line.length() && line[i] != '"')
                text.push_back(line[i++]);

            if (line[i] != '"')
                throw LexicalError("Nezatvoreni navodnici.");
            tokens.push_back({text, true});
            i++;
        }
        else
        {
            std::string text;
            while (i < line.length() && !isWhitespace(line[i]))
                text.push_back(line[i++]);

            tokens.push_back({text, false});
        }
    }

    return tokens;
}

bool Lexer::isWhitespace(char c)
{
    return c == ' ' || c == '\t';
}
