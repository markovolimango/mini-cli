#ifndef CLI_PROMPTFACTORY_H
#define CLI_PROMPTFACTORY_H

#include "IFactory.h"

class PromptFactory : public IFactory
{
public:
    PromptFactory();

    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};

inline PromptFactory::PromptFactory()
{
    Registry::registerFactory("prompt", this);
}


#endif
