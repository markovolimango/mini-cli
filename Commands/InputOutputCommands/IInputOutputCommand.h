#ifndef CLI_IINPUTOUTPUTCOMMAND_H
#define CLI_IINPUTOUTPUTCOMMAND_H

#include "../Command.h"

class IInputOutputCommand : public ICommand
{
public:
    explicit IInputOutputCommand(std::string name);

    void redirectInput(std::shared_ptr<std::istream> inRedirect) override;
    void redirectOutput(std::shared_ptr<std::ostream> outRedirect) override;
};


inline IInputOutputCommand::IInputOutputCommand(std::string name) :
    ICommand(std::move(name))
{
}

inline void IInputOutputCommand::redirectInput(const std::shared_ptr<std::istream> inRedirect)
{
    if (m_in != nullptr)
        ICommand::redirectInput(inRedirect);
    m_in = inRedirect;
}

inline void IInputOutputCommand::redirectOutput(const std::shared_ptr<std::ostream> outRedirect)
{
    if (m_out != nullptr)
        ICommand::redirectOutput(outRedirect);
    m_out = outRedirect;
}

#endif
