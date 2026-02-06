#include "Program.h"
#include "../Parsing/Parser.h"
#include "../Executor/Executor.h"
#include <string>

void Program::run(std::istream& inCmd, std::istream& inData, std::ostream& out, std::ostream& err)
{
    std::string line;

    if (&inCmd == &std::cin)
        std::cout << ICommand::getPrompt() << " ";
    while (std::getline(inCmd, line))
    {
        try
        {
            auto tokens = Lexer::tokenizeLine(line);
            if (tokens.empty()) continue;
            auto pipeline = Parser::parseLine(tokens);
            Executor::executePipeline(pipeline, inData, out);
        }
        catch (std::exception& e) { err << e.what() << "\n"; }

        if (&inData == &std::cin && inData.eof())
        {
            inData.clear();
            clearerr(stdin);
        }

        if (inCmd.eof() && &inCmd == &std::cin)
        {
            inCmd.clear();
            clearerr(stdin);
        }

        if (&inCmd == &std::cin)
            std::cout << ICommand::getPrompt() << " ";
    }
}
