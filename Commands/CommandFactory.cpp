#include "CommandFactory.h"
#include "../Errors/Errors.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string& name, const std::vector<Argument>& arguments)
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

    throw SyntaxError("Nepostojeca komanda \"" + name + "\".");
}

EchoCommand CommandFactory::createEchoCommand(const std::vector<Argument>& arguments)
{
    if (arguments.size() > 1)
        throw SyntaxError("Previse argumenata.");

    if (arguments.size() == 1)
    {
        if (arguments[0].getType() == ArgumentType::Option)
            throw SyntaxError("Kommanda ne podrzava opcije.");
        return EchoCommand(arguments[0].getText(), arguments[0].getType() == ArgumentType::Normal);
    }

    return {};
}

TimeCommand CommandFactory::createTimeCommand(const std::vector<Argument>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Previse argumenata.");

    return {};
}

DateCommand CommandFactory::createDateCommand(const std::vector<Argument>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Previse argumenata.");

    return {};
}

TouchCommand CommandFactory::createTouchCommand(const std::vector<Argument>& arguments)
{
    if (arguments.size() != 1)
        throw SyntaxError("Nevalidan broj argumenata.");

    if (arguments[0].getType() != ArgumentType::Normal)
        throw SyntaxError("Nevalidan tip argumenta.");

    return TouchCommand(arguments[0].getText());
}

WCCommand CommandFactory::createWCCommand(const std::vector<Argument>& arguments)
{
    if (arguments.empty() || arguments.size() > 2)
        throw SyntaxError("Nevalidan broj argumenata.");

    bool countsWords;
    if (arguments[0].getType() != ArgumentType::Option)
        throw SyntaxError("Nevalidan tip argumenta.");

    if (arguments[0].getText() == "-w")
        countsWords = true;
    else if (arguments[0].getText() == "-c")
        countsWords = false;
    else
        throw SyntaxError("Nevalidna opcija.");

    if (arguments.size() == 1)
        return {countsWords};
    if (arguments[1].getType() == ArgumentType::Normal)
        return {countsWords, arguments[1].getText(), true};
    if (arguments[1].getType() == ArgumentType::Quoted)
        return {countsWords, arguments[1].getText(), false};

    throw SyntaxError("Nevalidan tip argumenta.");
}
