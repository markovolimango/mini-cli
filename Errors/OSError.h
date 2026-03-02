#ifndef CLI_OSERROR_H
#define CLI_OSERROR_H

#include "Error.h"

class OSError : public Error
{
public:
    OSError(std::string const& message);
};

inline OSError::OSError(std::string const& message) :
    Error("OS Error: " + message)
{
}

#endif //CLI_OSERROR_H
