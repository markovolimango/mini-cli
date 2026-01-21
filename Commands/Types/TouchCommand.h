#ifndef CLI_TOUCHCOMMAND_H
#define CLI_TOUCHCOMMAND_H

#include "../Command.h"
#include <utility>

class TouchCommand : public Command
{
public:
    explicit TouchCommand(std::string filename);

    void execute(std::istream& in, std::ostream& out) override;

private:
    std::string m_filename;
};

#endif
