#include "HeadCommand.h"

void HeadCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    if (m_n < 0)
        throw SemanticError("N ne sme biti negativan.");

    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    std::string text, line;
    int i = 0;
    while (i < m_n && std::getline(in, line))
    {
        text.append(line);
        text.push_back('\n');
        i++;
    }
    out << text;
}
