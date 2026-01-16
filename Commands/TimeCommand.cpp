#include "TimeCommand.h"
#include <chrono>
#include <format>

void TimeCommand::execute(std::istream& in, std::ostream& out)
{
    auto now = std::chrono::system_clock::now();
    const std::string time = std::format("{:%T}", now);
    out << time << '\n';
}
