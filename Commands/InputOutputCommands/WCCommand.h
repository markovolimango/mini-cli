#ifndef CLI_WCCOMMAND_H
#define CLI_WCCOMMAND_H

#include "IInputOutputCommand.h"

class WCCommand : public IInputOutputCommand
{
public:
    explicit WCCommand(bool countWords, std::shared_ptr<std::istream> in);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    bool m_countWords;

    static unsigned countWords(std::istream& in);
    static unsigned countChars(std::istream& in);
};


inline WCCommand::WCCommand(const bool countWords, std::shared_ptr<std::istream> in) :
    IInputOutputCommand("wc"),
    m_countWords(countWords)
{
    m_in = in;
}

#endif
