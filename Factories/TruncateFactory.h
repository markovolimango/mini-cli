#ifndef CLI_TRUNCATEFACTORY_H
#define CLI_TRUNCATEFACTORY_H

#include "IFactory.h"

class TruncateFactory : public IFactory
{
public:
    TruncateFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};

inline TruncateFactory::TruncateFactory()
{
    Registry::registerFactory("truncate", this);
}


#endif //CLI_TRUNCATEFACTORY_H
