#include "CommandFactory.h"
#include "../errors/Errors.h"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string& name, const std::vector<Argument>& arguments)
{
    if (name == "echo")
        return std::make_unique<EchoCommand>(createEchoCommand(arguments));
    if (name == "time")
        return std::make_unique<TimeCommand>(createTimeCommand(arguments));
    if (name == "date")
        return std::make_unique<DateCommand>(createDateCommand(arguments));

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
        return EchoCommand(arguments[0].getText(), arguments[0].getType() == ArgumentType::Filename);
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
