#ifndef CLI_SYNTAXERROR_H
#define CLI_SYNTAXERROR_H

#include "Error.h"

class SyntaxError : public Error
{
public:
    SyntaxError(const std::string& message);
};

inline SyntaxError::SyntaxError(const std::string& message) :
    Error("Syntax error: " + message)
{
}


#endif //CLI_SYNTAXERROR_H
