#include "CommandFactory.h"
#include <fstream>
#include <sstream>
#include "../../Errors/Errors.h"
#include <vector>
#include "../BatchCommand.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string& name, const std::vector<Token>& arguments)
{
    if (name == "echo")
        return std::make_unique<EchoCommand>(createEchoCommand(arguments));
    if (name == "time")
        return std::make_unique<TimeCommand>(createTimeCommand(arguments));
    if (name == "date")
        return std::make_unique<DateCommand>(createDateCommand(arguments));
    if (name == "touch")
        return std::make_unique<TouchCommand>(createTouchCommand(arguments));
    if (name == "wc")
        return std::make_unique<WCCommand>(createWCCommand(arguments));
    if (name == "batch")
        return std::make_unique<BatchCommand>(createBatchCommand(arguments));

    throw UnknownCommandError("\"" + name + "\".");
}

EchoCommand CommandFactory::createEchoCommand(const std::vector<Token>& arguments)
{
    if (arguments.size() > 1)
        throw SyntaxError("Previse argumenata.");

    std::shared_ptr<std::istream> in = nullptr;
    if (arguments.size() == 1)
    {
        const auto& arg = arguments[0];
        if (arg.getType() == TokenType::Normal)
            in = std::make_shared<std::ifstream>(arg.getText());
        else if (arg.getType() == TokenType::Quoted)
            in = std::make_shared<std::istringstream>(arg.getText());
        else
            throw SyntaxError("Nevalidan tip argumenta.");
    }
    return EchoCommand(in);
}

TimeCommand CommandFactory::createTimeCommand(const std::vector<Token>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Previse argumenata.");

    return TimeCommand();
}

DateCommand CommandFactory::createDateCommand(const std::vector<Token>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Previse argumenata.");

    return DateCommand();
}

TouchCommand CommandFactory::createTouchCommand(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Normal)
        throw SyntaxError("Nevalidan tip argumenta.");

    return TouchCommand(arguments[0].getText());
}

WCCommand CommandFactory::createWCCommand(const std::vector<Token>& arguments)
{
    if (arguments.empty() || arguments.size() > 2)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != TokenType::Option)
        throw SyntaxError("Nevalidan tip argumenta.");

    bool countWords;
    if (arguments[0].getText() == "-w")
        countWords = true;
    else if (arguments[0].getText() == "-c")
        countWords = false;
    else
        throw SyntaxError("Nevalidna opcija" + arguments[0].getText() + ".");

    std::shared_ptr<std::istream> in = nullptr;
    if (arguments.size() != 1)
    {
        const auto& arg = arguments[1];
        if (arg.getType() == TokenType::Normal)
            in = std::make_shared<std::ifstream>(arg.getText());
        else if (arg.getType() == TokenType::Quoted)
            in = std::make_shared<std::istringstream>(arg.getText());
        else
            throw SyntaxError("Nevalidan tip argumenta.");
    }
    return WCCommand(countWords, in);
}

BatchCommand CommandFactory::createBatchCommand(const std::vector<Token>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    return BatchCommand(arguments[0].getText());
}
