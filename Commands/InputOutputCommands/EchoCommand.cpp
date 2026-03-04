#include "EchoCommand.h"
#include "../../Errors/Error.h"
#include <fstream>
#include <iostream>
#include <sstream>

void EchoCommand::execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err)
{
    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    std::string text, line;
    while (getline(in, line))
    {
        text.append(line);
        if (!in.eof())
            text.push_back('\n');
    }

    out << text;
}
