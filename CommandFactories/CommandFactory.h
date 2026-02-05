#ifndef CLI_COMMANDFACTORY_H
#define CLI_COMMANDFACTORY_H

#include "../Commands/Command.h"
#include "../Commands/OutputCommands/DateCommand.h"
#include "../Commands/InputOutputCommands/EchoCommand.h"
#include "../Commands/OutputCommands/TimeCommand.h"
#include "../Commands/TouchCommand.h"
#include "../Commands/InputOutputCommands/WCCommand.h"
#include "../Parsing/Token.h"
#include <memory>

#include "../Commands/OutputCommands/BatchCommand.h"

class CommandFactory
{
public:
    static std::unique_ptr<ICommand> createCommand(const std::string& name, const std::vector<Token>& arguments);

private:
    static EchoCommand createEchoCommand(const std::vector<Token>& arguments);
    static TimeCommand createTimeCommand(const std::vector<Token>& arguments);
    static DateCommand createDateCommand(const std::vector<Token>& arguments);
    static TouchCommand createTouchCommand(const std::vector<Token>& arguments);
    static WCCommand createWCCommand(const std::vector<Token>& arguments);
    static BatchCommand createBatchCommand(const std::vector<Token>& arguments);
};


#endif
