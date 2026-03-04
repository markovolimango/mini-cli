#ifndef CLI_HEADCOMMAND_H
#define CLI_HEADCOMMAND_H

#include "IInputOutputCommand.h"

class HeadCommand : public IInputOutputCommand
{
public:
    explicit HeadCommand(int n, std::shared_ptr<std::istream> in);
    void execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err) override;

private:
    const int m_n;
};


inline HeadCommand::HeadCommand(const int n, std::shared_ptr<std::istream> in) :
    IInputOutputCommand("head"),
    m_n(n)
{
    m_in = std::move(in);
}


#endif //CLI_HEADCOMMAND_H
