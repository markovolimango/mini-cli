#include "Lexer.h"
#include <functional>
#include "../Errors/LexicalError.h"

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
            text.append(readUntil(line, i, [](const char c) { return c == '"'; }, true));
            if (i >= line.length())
                throw LexicalError("Unclosed quotes", line, i);
            text.push_back(line[i++]);
            tokens.emplace_back(text);
        }
        else if (line[i] == '-')
        {
            std::string text;
            text.push_back(line[i++]);

            if (i >= line.length())
                throw LexicalError("Empty option", line, i);

            if (line[i] == '"')
            {
                text.push_back(line[i++]);
                text.append(readUntil(line, i, [](const char c) { return c == '"'; }, true));
                if (line[i] != '"')
                    throw LexicalError("Unclosed quotes", line, i);
                text.push_back(line[i++]);
            }
            else
                text.append(readUntil(line, i, [](const char c) { return isWhitespace(c); }));
            tokens.emplace_back(text);
        }
        else if (isOperator(line[i]))
        {
            std::string text;
            text.push_back(line[i++]);
            if (text == ">" && i < line.length() && line[i] == '>')
                text.push_back(line[i++]);
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
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::isLegal(const char c)
{
    return
        isWhitespace(c) ||
        'a' <= c && c <= 'z' ||
        'A' <= c && c <= 'Z' ||
        '0' <= c && c <= '9' ||
        c == '_' || c == '.' || c == '-' ||
        c == '-' || c == '|' || c == '<' || c == '>' || c == '\"';
}

bool Lexer::isOperator(char c)
{
    return c == '|' || c == '>' || c == '<';
}

std::string Lexer::readUntil(const std::string& line, size_t& i, const std::function<bool (char)>& endCondition,
                             bool ignoreIllegal)
{
    std::string text;
    while (i < line.size() && !endCondition(line[i]))
    {
        if (!ignoreIllegal && !isLegal(line[i]))
            throw LexicalError("Illegal character.", line, i);
        text.push_back(line[i++]);
    }
    return text;
}
