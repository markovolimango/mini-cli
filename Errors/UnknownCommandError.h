#ifndef CLI_UNKNOWNCOMMANDERROR_H
#define CLI_UNKNOWNCOMMANDERROR_H

#include "Error.h"


class UnknownCommandError : public Error
{
public:
    explicit UnknownCommandError(std::string command);
};

inline UnknownCommandError::UnknownCommandError(std::string command) :
    Error("Unknown command: " + std::move(command))
{
}


#endif //CLI_UNKNOWNCOMMANDERROR_H
