#ifndef CLI_BATCHCOMMAND_H
#define CLI_BATCHCOMMAND_H

#include "Base/Command.h"
#include "../Program/Program.h"

class BatchCommand : public OutputCommand
{
public:
    explicit BatchCommand(std::string filename);

    void execute(std::istream& inDefault, std::ostream& outDefault) override;

private:
    std::string m_filename;
};


#endif
