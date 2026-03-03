#include "WCCommand.h"
#include "../../Errors/Error.h"
#include <fstream>
#include <iostream>
#include <sstream>

void WCCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& in = getInputStream(inDefault);
    auto& out = getOutputStream(outDefault);

    const unsigned count = m_countWords ? countWords(in) : countChars(in);

    out << count << "\n";
}

unsigned WCCommand::countWords(std::istream& in)
{
    std::string line;
    unsigned count = 0;
    while (std::getline(in, line))
    {
        size_t i = 0;
        while (i < line.length())
        {
            if (std::isspace(line[i]))
                while (i < line.length() && std::isspace(line[i]))
                    i++;
            if (i >= line.length())
                break;

            count++;

            while (i < line.size() && !std::isspace(line[i]))
                i++;
        }
    }

    return count;
}

unsigned WCCommand::countChars(std::istream& in)
{
    unsigned count = 0;
    std::string line;

    while (std::getline(in, line))
    {
        count += line.length();
        if (!in.eof())
            count++;
    }

    return count;
}
