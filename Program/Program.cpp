#include "Program.h"
#include "../Parsing/Parser.h"
#include "Executor.h"
#include <string>

void Program::run(std::istream& in, std::ostream& out, std::ostream& err)
{
    std::string line;

    std::cout << "$ ";
    while (std::getline(in, line))
    {
        try
        {
            auto tokens = Lexer::tokenize(line);
            if (tokens.empty()) continue;
            auto pipeline = Parser::parseLine(tokens);
            Executor::execute(pipeline);
        }
        catch (std::exception& e) { err << e.what() << "\n"; }

        if (in.eof())
        {
            in.clear();
            if (&in == &std::cin)
                clearerr(stdin);
        }

        std::cout << "$ ";
    }
}
