#ifndef CLI_TOUCHCOMMAND_H
#define CLI_TOUCHCOMMAND_H

#include "ICommand.h"
#include <utility>

class TouchCommand : public ICommand
{
public:
    explicit TouchCommand(std::string filename);

    void execute(std::istream& in, std::ostream& out, std::ostream& err) override;

private:
    std::string m_filename;
};


inline TouchCommand::TouchCommand(std::string filename) :
    ICommand("touch"),
    m_filename(std::move(filename))
{
}

#endif
