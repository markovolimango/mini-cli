#ifndef CLI_DATEFACTORY_H
#define CLI_DATEFACTORY_H

#include "IFactory.h"
#include "../Commands/OutputCommands/DateCommand.h"

class DateFactory : public IFactory
{
public:
    DateFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline DateFactory::DateFactory()
{
    Registry::registerFactory("date", this);
}
#endif
