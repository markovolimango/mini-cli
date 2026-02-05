#ifndef CLI_OUTPUTCOMMAND_H
#define CLI_OUTPUTCOMMAND_H

#include <utility>

#include "../ICommand.h"

class IOutputCommand : public ICommand
{
public:
    explicit IOutputCommand(std::string name);

    void redirectOutput(std::shared_ptr<std::ostream> outRedirect) override;
};


inline IOutputCommand::IOutputCommand(std::string name) :
    ICommand(std::move(name))
{
}

inline void IOutputCommand::redirectOutput(const std::shared_ptr<std::ostream> outRedirect)
{
    if (m_out != nullptr)
        ICommand::redirectOutput(outRedirect);
    m_out = outRedirect;
}

#endif
