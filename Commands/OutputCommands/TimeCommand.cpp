#include "TimeCommand.h"
#include <chrono>
#include <format>

void TimeCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    auto& out = getOutputStream(outDefault);

    auto now = std::chrono::system_clock::now();
    const std::string time = std::format("{:%T}", now);
    out << time;
}
