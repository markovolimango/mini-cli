#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include <istream>
#include <memory>
#include <ostream>
#include <utility>
#include "../Errors/Errors.h"

class ICommand
{
public:
    explicit ICommand(std::string name);
    virtual ~ICommand() = default;

    virtual void execute(std::istream& inDefault, std::ostream& outDefault) = 0;

    virtual void redirectInput(std::shared_ptr<std::istream> inRedirect);
    virtual void redirectOutput(std::shared_ptr<std::ostream> outRedirect);

    static std::string getPrompt();

protected:
    std::shared_ptr<std::istream> m_in;
    std::shared_ptr<std::ostream> m_out;

    std::istream& getInputStream(std::istream& inDefault) const;
    std::ostream& getOutputStream(std::ostream& outDefault) const;

    static void setPrompt(std::string new_prompt);

private:
    static std::string prompt;

    std::string m_name;
};


inline ICommand::ICommand(std::string name) :
    m_name(std::move(name))
{
}

inline void ICommand::redirectInput(std::shared_ptr<std::istream> inRedirect)
{
    throw SemanticError("Redirekcija ulaza nije moguca.");
}

inline void ICommand::redirectOutput(std::shared_ptr<std::ostream> outRedirect)
{
    throw SemanticError("Redirekcija izlaza nije moguca.");
}

inline std::istream& ICommand::getInputStream(std::istream& inDefault) const
{
    return m_in ? *m_in : inDefault;
}

inline std::ostream& ICommand::getOutputStream(std::ostream& outDefault) const
{
    return m_out ? *m_out : outDefault;
}

inline std::string ICommand::getPrompt()
{
    return prompt;
}

inline void ICommand::setPrompt(std::string new_prompt)
{
    prompt = std::move(new_prompt);
}


#endif //CLI_COMMAND_H
