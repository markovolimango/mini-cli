#ifndef CLI_ARGUMENT_H
#define CLI_ARGUMENT_H

#include <string>
#include <utility>

enum class ArgumentType
{
    Normal,
    Quoted,
    Option
};

class Argument
{
public:
    Argument(std::string text, ArgumentType type);

    [[nodiscard]] ArgumentType getType() const;
    [[nodiscard]] const std::string& getText() const;

private:
    const std::string m_text;
    const ArgumentType m_type;
};


inline Argument::Argument(std::string text, const ArgumentType type) :
    m_text(std::move(text)),
    m_type(type)
{
}

inline ArgumentType Argument::getType() const
{
    return m_type;
}

inline const std::string& Argument::getText() const
{
    return m_text;
}

#endif //CLI_ARGUMENT_H
