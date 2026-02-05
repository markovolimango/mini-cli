#ifndef CLI_WCFACTORY_H
#define CLI_WCFACTORY_H

#include "IFactory.h"

class WCFactory : public IFactory
{
public:
    WCFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline WCFactory::WCFactory()
{
    Registry::registerFactory("wc", this);
}

#endif
