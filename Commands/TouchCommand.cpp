#include "TouchCommand.h"
#include "../Errors/Error.h"
#include <filesystem>
#include <fstream>
#include <utility>

void TouchCommand::execute(std::istream& in, std::ostream& out)
{
    if (std::filesystem::exists(m_filename))
        throw SemanticError("The file \"" + m_filename + "\" already exists.");

    if (!std::ofstream(m_filename))
        throw OSError("Unable to create file.");
}
