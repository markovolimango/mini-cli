#ifndef CLI_BATCHFACTORY_H
#define CLI_BATCHFACTORY_H

#include "IFactory.h"

class BatchFactory : IFactory
{
public:
    BatchFactory();

    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline BatchFactory::BatchFactory()
{
    Registry::registerFactory("batch", this);
}

#endif
