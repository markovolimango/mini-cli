#ifndef CLI_TOUCHFACTORY_H
#define CLI_TOUCHFACTORY_H
#include "IFactory.h"


class TouchFactory : public IFactory
{
public:
    TouchFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};

inline TouchFactory::TouchFactory()
{
    Registry::registerFactory("touch", this);
}

#endif
