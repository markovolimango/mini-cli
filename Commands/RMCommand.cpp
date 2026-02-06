#include "RMCommand.h"
#include <filesystem>

void RMCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    if (!std::filesystem::remove(m_filename))
        throw OSError("Fajl nije obrisan.");
}
