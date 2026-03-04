#ifndef CLI_PROMPTCOMMAND_H
#define CLI_PROMPTCOMMAND_H

#include <utility>
#include "ICommand.h"

class PromptCommand : public ICommand
{
public:
    PromptCommand(std::string prompt);

    void execute(std::istream& in, std::ostream& out, std::ostream& err) override;

private:
    std::string m_prompt;
};


inline PromptCommand::PromptCommand(std::string prompt) :
    ICommand("prompt"),
    m_prompt(std::move(prompt))
{
}

inline void PromptCommand::execute(std::istream& in, std::ostream& out, std::ostream& err)
{
    setPrompt(m_prompt);
}


#endif
