#ifndef CLI_TIMEFACTORY_H
#define CLI_TIMEFACTORY_H

#include "IFactory.h"
#include "../Commands/OutputCommands/TimeCommand.h"

class TimeFactory : public IFactory
{
public:
    TimeFactory();
    std::unique_ptr<ICommand> create(const std::vector<Token>& arguments) override;
};


inline TimeFactory::TimeFactory()
{
    Registry::registerFactory("time", this);
}
#endif
