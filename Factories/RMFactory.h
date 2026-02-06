#ifndef CLI_RMFACTORY_H
#define CLI_RMFACTORY_H

#include "IFactory.h"

class RMFactory : public IFactory
{
public:
    RMFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline RMFactory::RMFactory()
{
    Registry::registerFactory("rm", this);
}


#endif //CLI_RMFACTORY_H
