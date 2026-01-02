#include "DateCommand.h"
#include <chrono>
#include <format>

void DateCommand::execute(std::istream& in, std::ostream& out, std::ostream& err)
{
    auto now = std::chrono::system_clock::now();
    const std::string date = std::format("{:%d.%m.%Y}", now);
    out << date;
}
