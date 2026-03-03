#include "DateFactory.h"

static DateFactory g_dateFactory;

std::unique_ptr<ICommand> DateFactory::create(const std::vector<Token>& arguments)
{
    if (!arguments.empty())
        throw SyntaxError("Invalid argument count");

    return std::make_unique<DateCommand>();
}
