#include "Token.h"
#include <utility>
#include "../Errors/Errors.h"

Token::Token(const std::string& text) :
    m_text(text),
    m_type(TokenType::Normal)
{
    if (text.empty())
        throw LexicalError("Prazan token");

    switch (text[0])
    {
    case '"':
        m_text = text.substr(1, text.size() - 2);
        m_type = TokenType::Quoted;
        break;
    case '-':
        m_text = text.substr(1, text.size() - 1);
        m_type = TokenType::Option;
        break;
    case '<':
        m_text = text.substr(1, text.size() - 1);
        m_type = TokenType::InRedirect;
        break;
    case '>':
        if (text.size() == 1)
            throw LexicalError("Prazna redirekcija");
        if (text[1] == '>')
        {
            m_text = text.substr(2, text.size() - 2);
            m_type = TokenType::OutRedirectApp;
        }
        else
        {
            m_text = text.substr(1, text.size() - 1);
            m_type = TokenType::OutRedirectTrunc;
        }
        break;
    case '|':
        m_text = "";
        m_type = TokenType::Pipe;
        break;
    default:
        m_text = text;
        m_type = TokenType::Normal;
        break;
    }
}

bool Token::isArgument() const
{
    return m_type == TokenType::Normal || m_type == TokenType::Quoted || m_type == TokenType::Option;
}
