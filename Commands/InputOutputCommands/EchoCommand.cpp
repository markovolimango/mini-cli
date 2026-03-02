#include "EchoCommand.h"
#include "../../Errors/Error.h"
#include <fstream>
#include <iostream>
#include <sstream>

void EchoCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    std::string text, line;
    while (getline(in, line))
    {
        text.append(line);
        if (!in.eof())
            text.append("\n");
    }
    //if (text[text.length() - 1] != '\n')
    //    text.push_back('\n');

    out << text;

    if (&out == &std::cout && text.back() != '\n')
        out << '\n';
}
