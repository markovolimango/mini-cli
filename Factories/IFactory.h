#ifndef CLI_IFACTORY_H
#define CLI_IFACTORY_H

#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "Registry.h"
#include "../Errors/SyntaxError.h"
#include "../Commands/ICommand.h"
#include "../Parsing/Token.h"

class IFactory
{
public:
    virtual ~IFactory() = default;

    virtual std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) = 0;

protected:
    static std::shared_ptr<std::istream> createIn(const Token& token);
};

#endif
