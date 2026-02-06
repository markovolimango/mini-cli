#include "TruncateCommand.h"
#include <filesystem>
#include <fstream>

void TruncateCommand::execute(std::istream& inDefault, std::ostream& outDefault)
{
    if (!std::filesystem::exists(m_filename))
        throw SemanticError("Fajl \"" + m_filename + "\" ne postoji.");

    if (!std::ofstream(m_filename, std::ios::trunc))
        throw OSError("Fajl nije obrisan.");
}
