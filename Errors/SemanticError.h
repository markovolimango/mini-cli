#ifndef CLI_SEMANTICERROR_H
#define CLI_SEMANTICERROR_H

#include "Error.h"

class SemanticError : public Error
{
public:
    SemanticError(const std::string& message);
};

inline SemanticError::SemanticError(const std::string& message) :
    Error("Semantic error: " + message)
{
}


#endif //CLI_SEMANTICERROR_H
