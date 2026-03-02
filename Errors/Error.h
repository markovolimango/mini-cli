#ifndef CLI_ERROR_H
#define CLI_ERROR_H

#include <stdexcept>
#include <string>
#include <utility>

class Error : public std::runtime_error
{
public:
    explicit Error() : runtime_error("")
    {
    }

    explicit Error(std::string message) : m_message(std::move(message)), runtime_error("")
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

    ~Error() override = default;

protected:
    mutable std::string m_message;
};


#endif
