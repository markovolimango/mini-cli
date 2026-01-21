#ifndef CLI_COMMANDFACTORY_H
#define CLI_COMMANDFACTORY_H

#include "../Base/Command.h"
#include "../DateCommand.h"
#include "../EchoCommand.h"
#include "../TimeCommand.h"
#include "../TouchCommand.h"
#include "../WCCommand.h"
#include "../../Parsing/Token.h"
#include <memory>

#include "../BatchCommand.h"

class CommandFactory
{
public:
    static std::unique_ptr<Command> createCommand(const std::string& name, const std::vector<Token>& arguments);

private:
    static EchoCommand createEchoCommand(const std::vector<Token>& arguments);
    static TimeCommand createTimeCommand(const std::vector<Token>& arguments);
    static DateCommand createDateCommand(const std::vector<Token>& arguments);
    static TouchCommand createTouchCommand(const std::vector<Token>& arguments);
    static WCCommand createWCCommand(const std::vector<Token>& arguments);
    static BatchCommand createBatchCommand(const std::vector<Token>& arguments);
};


#endif
