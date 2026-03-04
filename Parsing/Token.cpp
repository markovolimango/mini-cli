#include "Token.h"
#include <utility>
#include "../Errors/SyntaxError.h"

Token::Token(const std::string& text) :
    m_text(text),
    m_type(TokenType::Normal)
{
    if (text.empty())
        throw SyntaxError("Prazan argument");

    switch (text[0])
    {
    case '"':
        m_text = text.substr(1, text.size() - 2);
        m_type = TokenType::Quoted;
        break;
    case '-':
        if (text[1] != '"')
        {
            m_text = text.substr(1, text.size() - 1);
            m_type = TokenType::Option;
        }
        else
        {
            m_text = text.substr(2, text.size() - 3);
            m_type = TokenType::OptionQuoted;
        }
        break;
    case '<':
        m_text = text;
        m_type = TokenType::Operator;
        break;
    case '>':
        m_text = text;
        m_type = TokenType::Operator;
        break;
    case '|':
        m_text = text;
        m_type = TokenType::Operator;
        break;
    default:
        m_text = text;
        m_type = TokenType::Normal;
        break;
    }
}

bool Token::isArgument() const
{
    return m_type != TokenType::Operator;
}
