#include "Lexer.h"
#include <functional>
#include "../Errors/Errors.h"

std::vector<Token> Lexer::tokenizeLine(const std::string& line)
{
    size_t i = 0;
    std::vector<Token> tokens;

    while (true)
    {
        readUntil(line, i, [](const char c) { return !isWhitespace(c); });
        if (i >= line.length())
            break;

        if (line[i] == '"')
        {
            std::string text;
            text.push_back(line[i++]);
            text.append(readUntil(line, i, [](const char c) { return c == '"'; }));
            if (line[i] != '"')
                throw LexicalError("Nezatvoreni navodnici.");
            text.push_back(line[i++]);
            tokens.emplace_back(text);
        }
        else if (line[i] == '<' || line[i] == '>')
        {
            std::string text;
            text.push_back(line[i++]);

            readUntil(line, i, [](const char c) { return !isWhitespace(c); });
            if (i >= line.length())
                throw LexicalError("Prazna redirekcija");

            text.append(readUntil(line, i, [](const char c) { return isWhitespace(c); }));

            tokens.emplace_back(text);
        }
        else if (line[i] == '-')
        {
            std::string text;
            text.push_back(line[i++]);

            if (i >= line.length())
                throw LexicalError("Prazan argument");

            if (line[i] == '"')
            {
                text.push_back(line[i++]);
                text.append(readUntil(line, i, [](const char c) { return c == '"'; }));
                if (line[i] != '"')
                    throw LexicalError("Nezatvoreni navodnici.");
                text.push_back(line[i++]);
            }
            else
                text.append(readUntil(line, i, [](const char c) { return isWhitespace(c); }));
            tokens.emplace_back(text);
        }
        else
        {
            tokens.emplace_back(readUntil(line, i, [](const char c) { return isWhitespace(c); }));
        }
    }

    return tokens;
}

bool Lexer::isWhitespace(const char c)
{
    return c == ' ' || c == '\t';
}

std::string Lexer::readUntil(const std::string& line, size_t& i, const std::function<bool (char)>& endCondition)
{
    std::string text;
    while (i < line.size() && !endCondition(line[i]))
        text.push_back(line[i++]);
    return text;
}
