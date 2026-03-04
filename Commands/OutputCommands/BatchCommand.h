#ifndef CLI_BATCHCOMMAND_H
#define CLI_BATCHCOMMAND_H

#include "IOutputCommand.h"
#include "../../Program/Program.h"

class BatchCommand : public IOutputCommand
{
public:
    explicit BatchCommand(std::shared_ptr<std::istream> in);

    void execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err) override;

private:
    std::shared_ptr<std::istream> m_inCmd;
};


inline BatchCommand::BatchCommand(std::shared_ptr<std::istream> in) :
    IOutputCommand("batch")
{
    m_inCmd = in;
}

#endif
