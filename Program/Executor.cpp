#include "Executor.h"

void Executor::execute(const Pipeline& pipeline)
{
    if (pipeline.commands.empty())
        return;

    pipeline.commands[0].command->execute(std::cin, std::cout);
}
