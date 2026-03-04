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
            line = line.substr(0, 512);
            auto tokens = Lexer::tokenizeLine(line);
            auto pipeline = Parser::parseLine(tokens);
            Executor::executePipeline(pipeline, inData, out, err);
        }
        catch (std::exception& e) { err << e.what(); }

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
            std::cout << "\n" << ICommand::getPrompt() << " ";
    }
}
