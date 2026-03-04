#include "DateCommand.h"
#include <chrono>
#include <format>

void DateCommand::execute(std::istream& inDefault, std::ostream& outDefault, std::ostream& err)
{
    std::ostream& out = getOutputStream(outDefault);

    auto now = std::chrono::system_clock::now();
    const std::string date = std::format("{:%d.%m.%Y}", now);
    out << date;
}
