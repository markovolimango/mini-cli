#ifndef CLI_ARGUMENT_H
#define CLI_ARGUMENT_H

#include <string>

enum class TokenType
{
    Normal,
    Quoted,
    Option,
    OptionQuoted,
    InRedirect,
    OutRedirectTrunc,
    OutRedirectApp,
    Pipe
};

class Token
{
public:
    explicit Token(const std::string& text);

    TokenType getType() const;
    const std::string& getText() const;

    bool isArgument() const;

private:
    std::string m_text;
    TokenType m_type;
};


inline TokenType Token::getType() const
{
    return m_type;
}

inline const std::string& Token::getText() const
{
    return m_text;
}

#endif //CLI_ARGUMENT_H
