#include "BatchCommand.h"
#include <fstream>
#include <utility>

void BatchCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    Program::run(*m_inCmd, in, out, out);
}
