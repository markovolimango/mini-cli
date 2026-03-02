#include "LexicalError.h"

LexicalError::LexicalError(std::string message, std::string line, size_t pos) :
    Error("Lexical error: " + std::move(message)),
    m_line(std::move(line)),
    m_pos(pos)
{
    m_message += "\n" + m_line + "\n";
    for (auto i = 0; i < m_pos; ++i)
        m_message.push_back(' ');
    m_message.push_back('^');
}
