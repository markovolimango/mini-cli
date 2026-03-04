#ifndef CLI_TRCOMMAND_H
#define CLI_TRCOMMAND_H

#include <utility>

#include "IInputOutputCommand.h"

class TRCommand : public IInputOutputCommand
{
public:
    explicit TRCommand(std::shared_ptr<std::istream> in, std::string what, std::string with);

    void execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err) override;

private:
    std::string m_what;
    std::string m_with;
};


inline TRCommand::TRCommand(std::shared_ptr<std::istream> in, std::string what, std::string with) :
    IInputOutputCommand("tr"),
    m_what(std::move(what)),
    m_with(std::move(with))
{
    m_in = std::move(in);
}

#endif //CLI_TRCOMMAND_H
