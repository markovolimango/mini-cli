#ifndef CLI_TRFACTORY_H
#define CLI_TRFACTORY_H

#include "IFactory.h"

class TRFactory : public IFactory
{
public:
    TRFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline TRFactory::TRFactory()
{
    Registry::registerFactory("tr", this);
}

#endif //CLI_TRFACTORY_H
