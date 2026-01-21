#include "BatchCommand.h"
#include <fstream>
#include <utility>

BatchCommand::BatchCommand(std::string filename) :
    OutputCommand("batch"),
    m_filename(std::move(filename))
{
}

void BatchCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& out = getOutputStream(outDefault);
    auto ifs = std::ifstream(m_filename);

    Program::run(ifs, inDefault, out, out);
}
