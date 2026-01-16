#include "EchoCommand.h"
#include "../Errors/Errors.h"
#include <fstream>
#include <iostream>
#include <sstream>


EchoCommand::EchoCommand(std::string text, const bool isFilename)
{
    if (isFilename)
        m_filename = std::move(text);
    else
        m_string = std::move(text);
}

void EchoCommand::execute(std::istream& in, std::ostream& out)
{
    if (!m_filename.empty())
    {
        auto ifs = std::ifstream(m_filename);
        if (!ifs)
            throw OSError("Fajl \"" + m_filename + "\" ne postoji.");

        return echoStream(ifs, out);
    }

    if (!m_string.empty())
    {
        auto ss = std::stringstream(m_string);
        return echoStream(ss, out);
    }

    return echoStream(in, out);
}


void EchoCommand::echoStream(std::istream& in, std::ostream& out)
{
    std::string text, line;
    while (getline(in, line))
    {
        text.append(line);
        if (!in.eof())
            text.append("\n");
    }

#ifndef _WIN32
    if (&in == &std::cin && &out == &std::cout)
        out << '\n';
#endif

    out << text << '\n';
}
