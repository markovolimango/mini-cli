#include <iostream>
#include <string>
#include <vector>
#include "Lexer.h"
#include "parser/Parser.h"
#include <unistd.h>
#include <chrono>
#include <format>

int main()
{
    std::string line;

    while (true)
    {
        std::cout << "$ ";

        if (!std::getline(std::cin, line))
        {
            break;
        }

        try
        {
            auto tokens = Lexer::tokenize(line);
            if (tokens.empty()) continue;
            auto pipeline = Parser::parse(tokens);
            if (pipeline.commands.empty()) continue;

            pipeline.commands[0].command->execute(std::cin, std::cout, std::cerr);
        }
        catch (std::exception& e) { std::cout << e.what() << std::endl; }

        if (std::cin.eof())
        {
            std::cin.clear();
            clearerr(stdin);
        }

        std::cout << std::endl;
    }
    return 0;
}
