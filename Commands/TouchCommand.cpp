#include "TouchCommand.h"
#include "../Errors/Errors.h"
#include <filesystem>
#include <fstream>

void TouchCommand::execute(std::istream& in, std::ostream& out, std::ostream& err)
{
    if (std::filesystem::exists(m_filename))
        throw SemanticError("Fajl vec postoji.");

    if (!std::ofstream(m_filename))
        throw SemanticError("Fajl nije napravljen.");
}
