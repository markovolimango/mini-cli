#include "Command.h"
#include <utility>
#include  "../Errors/Errors.h"

Command::Command(std::string name) :
    m_name(std::move(name))
{
}

void Command::redirectInput(const std::shared_ptr<std::istream> inRedirect)
{
    throw SemanticError("Redirekcija ulaza nije moguca.");
}

void Command::redirectOutput(const std::shared_ptr<std::ostream> outRedirect)
{
    throw SemanticError("Redirekcija izlaza nije moguca.");
}

std::istream& Command::getInputStream(std::istream& inDefault) const
{
    return m_in ? *m_in : inDefault;
}

std::ostream& Command::getOutputStream(std::ostream& outDefault) const
{
    return m_out ? *m_out : outDefault;
}

void InputCommand::redirectInput(const std::shared_ptr<std::istream> inRedirect)
{
    if (m_in != nullptr)
        Command::redirectInput(inRedirect);

    m_in = inRedirect;
}

void OutputCommand::redirectOutput(const std::shared_ptr<std::ostream> outRedirect)
{
    if (m_out != nullptr)
        Command::redirectOutput(outRedirect);

    m_out = outRedirect;
}

void InputOutputCommand::redirectInput(std::shared_ptr<std::istream> inRedirect)
{
    if (m_in != nullptr)
        Command::redirectInput(inRedirect);

    m_in = inRedirect;
}

void InputOutputCommand::redirectOutput(std::shared_ptr<std::ostream> outRedirect)
{
    if (m_out != nullptr)
        Command::redirectOutput(outRedirect);

    m_out = outRedirect;
}
