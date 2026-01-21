#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include <istream>
#include <memory>
#include <ostream>
#include <utility>

class Command
{
public:
    explicit Command(std::string name);
    virtual ~Command() = default;

    virtual void execute(std::istream& inDefault, std::ostream& outDefault) = 0;

    virtual void redirectInput(std::shared_ptr<std::istream> inRedirect);
    virtual void redirectOutput(std::shared_ptr<std::ostream> outRedirect);

protected:
    std::string m_name;

    std::shared_ptr<std::istream> m_in;
    std::shared_ptr<std::ostream> m_out;

    std::istream& getInputStream(std::istream& inDefault) const;
    std::ostream& getOutputStream(std::ostream& outDefault) const;
};

class InputCommand : public Command
{
public:
    explicit InputCommand(std::string name) : Command(std::move(name))
    {
    }

    void redirectInput(std::shared_ptr<std::istream> inRedirect) override;
};

class OutputCommand : public Command
{
public:
    explicit OutputCommand(std::string name) : Command(std::move(name))
    {
    }

    void redirectOutput(std::shared_ptr<std::ostream> outRedirect) override;
};

class InputOutputCommand : public Command
{
public:
    explicit InputOutputCommand(std::string name) : Command(std::move(name))
    {
    }

    void redirectInput(std::shared_ptr<std::istream> inRedirect) override;
    void redirectOutput(std::shared_ptr<std::ostream> outRedirect) override;
};

#endif //CLI_COMMAND_H
