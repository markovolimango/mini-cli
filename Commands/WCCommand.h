#ifndef CLI_WCCOMMAND_H
#define CLI_WCCOMMAND_H

#include "Command.h"

class WCCommand : public Command
{
public:
    WCCommand(bool countsWords);
    WCCommand(bool countsWords, const std::string& text, bool isFilename);

    void execute(std::istream& in, std::ostream& out, std::ostream& err) override;

private:
    bool m_countsWords;
    std::string m_filename;
    std::string m_string;

    static unsigned countWords(std::istream& in);
    static unsigned countChars(std::istream& in);
};


#endif
