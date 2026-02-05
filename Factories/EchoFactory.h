#ifndef CLI_ECHOFACTORY_H
#define CLI_ECHOFACTORY_H

#include "IFactory.h"

class EchoFactory : public IFactory
{
public:
    EchoFactory();

    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline EchoFactory::EchoFactory()
{
    Registry::registerFactory("echo", this);
}

#endif
