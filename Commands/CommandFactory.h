#ifndef CLI_COMMANDFACTORY_H
#define CLI_COMMANDFACTORY_H

#include "Command.h"
#include "DateCommand.h"
#include "EchoCommand.h"
#include "TimeCommand.h"
#include "TouchCommand.h"
#include "WCCommand.h"
#include "../Parsing/Argument.h"
#include <memory>

class CommandFactory
{
public:
    static std::unique_ptr<Command> createCommand(const std::string& name, const std::vector<Argument>& arguments);

private:
    static EchoCommand createEchoCommand(const std::vector<Argument>& arguments);
    static TimeCommand createTimeCommand(const std::vector<Argument>& arguments);
    static DateCommand createDateCommand(const std::vector<Argument>& arguments);
    static TouchCommand createTouchCommand(const std::vector<Argument>& arguments);
    static WCCommand createWCCommand(const std::vector<Argument>& arguments);
};


#endif
