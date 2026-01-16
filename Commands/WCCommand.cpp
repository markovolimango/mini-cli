#include "WCCommand.h"
#include "../Errors/Errors.h"
#include <fstream>
#include <iostream>
#include <sstream>

WCCommand::WCCommand(const bool countsWords) :
    m_countsWords(countsWords)
{
}

WCCommand::WCCommand(const bool countsWords, const std::string& text, const bool isFilename) :
    m_countsWords(countsWords)
{
    if (isFilename)
        m_filename = text;
    else
        m_string = text;
}

void WCCommand::execute(std::istream& in, std::ostream& out)
{
    if (!m_filename.empty())
    {
        std::ifstream ifs(m_filename);
        if (!ifs.is_open())
            throw OSError("Fajl " + m_filename + " ne postoji.");

        if (m_countsWords)
            out << countWords(ifs);
        else
            out << countChars(ifs);
    }
    else if (!m_string.empty())
    {
        std::stringstream ss(m_string);

        if (m_countsWords)
            out << countWords(ss);
        else
            out << countChars(ss);
    }
    else
    {
        unsigned count;
        if (m_countsWords)
            count = countWords(in);
        else
            count = countChars(in);

#ifndef _WIN32
        if (&in == &std::cin && &out == &std::cout)
            out << '\n';
#endif
        out << count;
    }
    out << '\n';
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
