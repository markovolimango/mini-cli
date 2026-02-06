#ifndef CLI_HEADFACTORY_H
#define CLI_HEADFACTORY_H

#include "IFactory.h"

class HeadFactory : public IFactory
{
public:
    HeadFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline HeadFactory::HeadFactory()
{
    Registry::registerFactory("head", this);
}

#endif //CLI_HEADFACTORY_H
