#ifndef CLI_RMCOMMAND_H
#define CLI_RMCOMMAND_H

#include "ICommand.h"

class RMCommand : public ICommand
{
public:
    explicit RMCommand(std::string filename);
    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    std::string m_filename;
};


inline RMCommand::RMCommand(std::string filename) :
    ICommand("rm"),
    m_filename(std::move(filename))
{
}

#endif //CLI_RMCOMMAND_H
