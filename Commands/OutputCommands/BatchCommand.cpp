#include "BatchCommand.h"
#include <fstream>
#include <utility>

void BatchCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& out = getOutputStream(outDefault);
    auto ifs = std::ifstream(m_filename);

    Program::run(ifs, inDefault, out, out);
}
