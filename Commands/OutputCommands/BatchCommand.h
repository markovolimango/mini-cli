#ifndef CLI_BATCHCOMMAND_H
#define CLI_BATCHCOMMAND_H

#include "OutputCommand.h"
#include "../../Program/Program.h"

class BatchCommand : public IOutputCommand
{
public:
    explicit BatchCommand(std::string filename);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    std::string m_filename;
};


inline BatchCommand::BatchCommand(std::string filename) :
    IOutputCommand("batch"),
    m_filename(std::move(filename))
{
}

#endif
