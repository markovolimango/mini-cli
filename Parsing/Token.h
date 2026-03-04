#ifndef CLI_ARGUMENT_H
#define CLI_ARGUMENT_H

#include <string>

enum class TokenType
{
    Normal,
    Quoted,
    Option,
    OptionQuoted,
    Operator
};

class Token
{
public:
    explicit Token(const std::string& text);

    [[nodiscard]] TokenType getType() const;
    [[nodiscard]] const std::string& getText() const;

    [[nodiscard]] bool isArgument() const;

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
