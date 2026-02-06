#ifndef CLI_TRUNCATECOMMAND_H
#define CLI_TRUNCATECOMMAND_H

#include <utility>

#include "ICommand.h"

class TruncateCommand : public ICommand
{
public:
    explicit TruncateCommand(std::string filename);
    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    std::string m_filename;
};


inline TruncateCommand::TruncateCommand(std::string filename) :
    ICommand("truncate"),
    m_filename(std::move(filename))
{
}

#endif
