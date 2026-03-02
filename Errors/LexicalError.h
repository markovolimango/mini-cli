#ifndef CLI_LEXICALERROR_H
#define CLI_LEXICALERROR_H
#include "Error.h"

#include <utility>


class LexicalError : public Error
{
public:
    LexicalError(std::string message, std::string line, size_t pos);

private:
    std::string m_line;
    size_t m_pos;
};


#endif //CLI_LEXICALERROR_H
