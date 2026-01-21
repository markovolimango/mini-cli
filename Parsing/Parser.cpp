#include "Parser.h"
#include "../Errors/Errors.h"
#include "../Commands/CommandFactory.h"

Pipeline Parser::parseLine(const std::vector<Token>& tokens)
{
    size_t i = 0;
    Pipeline pipeline;

    while (i < tokens.size())
    {
        if (tokens[i].isQuoted)
            throw SyntaxError("Ime komande ne moze biti pod navodnicima.");

        std::string name = tokens[i].text;
        i++;

        std::vector<Argument> arguments;
        while (i < tokens.size() && tokens[i].text != "|")
        {
            if (tokens[i].isQuoted)
                arguments.emplace_back(tokens[i].text, ArgumentType::Quoted);
            else if (tokens[i].text[0] == '-')
                arguments.emplace_back(tokens[i].text, ArgumentType::Option);
            else
                arguments.emplace_back(tokens[i].text, ArgumentType::Normal);
            i++;
        }
        if (i < tokens.size() && tokens[i].text == "|")
            i++;

        pipeline.commands.emplace_back(CommandFactory::createCommand(name, arguments), "", "");
    }

    return pipeline;
}
