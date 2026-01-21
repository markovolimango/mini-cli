#include "TouchCommand.h"
#include "../../Errors/Errors.h"
#include <filesystem>
#include <fstream>
#include <utility>

TouchCommand::TouchCommand(std::string filename) :
    Command("touch"),
    m_filename(std::move(filename))
{
}

void TouchCommand::execute(std::istream& in, std::ostream& out)
{
    if (std::filesystem::exists(m_filename))
        throw SemanticError("Fajl \"" + m_filename + "\" vec postoji.");

    if (!std::ofstream(m_filename))
        throw SemanticError("Fajl nije napravljen.");
}
