#include "TRCommand.h"

#include <iostream>
#include <regex>

void TRCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    std::string text, line;
    while (getline(in, line))
    {
        line = std::regex_replace(line, std::regex(m_what), m_with);

        text.append(line);
        if (!in.eof())
            text.append("\n");
    }
    if (text[text.length() - 1] != '\n')
        text.push_back('\n');

    out << text;
}
