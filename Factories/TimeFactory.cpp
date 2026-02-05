#include "TimeFactory.h"

static TimeFactory g_timeFactory;

std::unique_ptr<ICommand> TimeFactory::create(const std::vector<Token>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Previse argumenata.");

    return std::make_unique<TimeCommand>();
}
