#include "Executor.h"
#include <fstream>
#include <sstream>

void Executor::executePipeline(const Pipeline& pipeline, std::istream& inDefault, std::ostream& outDefault)
{
    std::string inString;
    for (size_t i = 0; i < pipeline.commandCalls.size(); i++)
    {
        auto& [command,
            inRedirect,
            outRedirect] = pipeline.commandCalls[i];

        if (inRedirect)
            command->redirectInput(inRedirect);
        if (outRedirect)
            command->redirectOutput(outRedirect);

        auto outStream = std::make_shared<std::ostringstream>("");
        if (i > 0)
            command->redirectInput(std::make_shared<std::istringstream>(inString));
        if (i < pipeline.commandCalls.size() - 1)
            command->redirectOutput(outStream);

        command->execute(inDefault, outDefault);

        inString = outStream->str();
    }
}
