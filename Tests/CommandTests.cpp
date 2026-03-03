#include <gtest/gtest.h>
#include "../Commands/InputOutputCommands/EchoCommand.h"
#include "../Commands/InputOutputCommands/WCCommand.h"
#include "../Commands/InputOutputCommands/HeadCommand.h"
#include "../Commands/InputOutputCommands/TRCommand.h"
#include "../Commands/OutputCommands/BatchCommand.h"
#include <sstream>
#include <memory>
#include <iostream>

TEST(CommandTests, EchoCommandTest)
{
    auto in = std::make_shared<std::istringstream>("Hello World!");
    std::ostringstream out;

    auto echo = EchoCommand(in);
    echo.execute(std::cin, out);

    EXPECT_EQ(out.str(), "Hello World!\n");
}

TEST(CommandTests, HeadCommandTest)
{
    auto in = std::make_shared<std::istringstream>(
        "Hello World!\n"
        "How are you?"
    );
    std::ostringstream out;

    auto head = HeadCommand(1, in);
    head.execute(std::cin, out);

    EXPECT_EQ(out.str(), "Hello World!\n");
}

TEST(CommandTests, WCCommandTest)
{
    auto in = std::make_shared<std::istringstream>(
        "A C++ program is a sequence of text files (typically header and source files) that contain declarations. "
        "They undergo translation to become an executable program, which is executed when the C++ implementation calls "
        "its main function."
    );
    std::ostringstream out;

    auto wc = WCCommand(true, in);
    wc.execute(std::cin, out);

    EXPECT_EQ(out.str(), "36\n");
}

TEST(CommandTests, TRCommandTest)
{
    auto in = std::make_shared<std::istringstream>(
        "Hello World!\n"
        "How are you?"
    );
    std::ostringstream out;

    auto tr = TRCommand(in, " ", "");
    tr.execute(std::cin, out);

    EXPECT_EQ(
        out.str(),
        "HelloWorld!\n"
        "Howareyou?"
    );
}

TEST(CommandTests, BatchCommandTest)
{
    auto in = std::make_shared<std::istringstream>(
        "echo \"mare\"\n"
        "wc -c \"mare\"\n"
    );
    std::ostringstream out;

    auto batch = BatchCommand(in);
    batch.execute(std::cin, out);

    EXPECT_EQ(
        out.str(),
        "mare\n"
        "4\n"
    );
}
