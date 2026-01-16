#include "TimeCommand.h"
#include <chrono>
#include <format>

void TimeCommand::execute(std::istream& in, std::ostream& out, std::ostream& err)
{
    auto now = std::chrono::system_clock::now();
    const std::string time = std::format("{:%T}", now);
    out << time << '\n';
}
