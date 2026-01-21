#ifndef CLI_WCCOMMAND_H
#define CLI_WCCOMMAND_H

#include "../Command.h"

class WCCommand : public InputOutputCommand
{
public:
    explicit WCCommand(bool countWords, std::shared_ptr<std::istream> in);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    bool m_countWords;

    static unsigned countWords(std::istream& in);
    static unsigned countChars(std::istream& in);
};


#endif
