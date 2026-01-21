#include "EchoCommand.h"
#include "../Errors/Errors.h"
#include <fstream>
#include <iostream>
#include <sstream>


EchoCommand::EchoCommand(std::shared_ptr<std::istream> in) :
    InputOutputCommand("echo")
{
    m_in = in;
}

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
    if (text[text.length() - 1] != '\n')
        text.push_back('\n');

    out << text;
}
