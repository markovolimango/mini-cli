#include <gtest/gtest.h>
#include "TestUtils.h"
#include "../Commands/InputOutputCommands/EchoCommand.h"
#include "../Commands/InputOutputCommands/WCCommand.h"
#include "../Commands/InputOutputCommands/HeadCommand.h"
#include "../Commands/InputOutputCommands/TRCommand.h"
#include "../Commands/OutputCommands/BatchCommand.h"
#include "../Commands/OutputCommands/DateCommand.h"
#include "../Commands/OutputCommands/TimeCommand.h"
#include "../Commands/PromptCommand.h"
#include "../Commands/RMCommand.h"
#include "../Commands/TouchCommand.h"
#include "../Commands/TruncateCommand.h"
#include <sstream>
#include <memory>
#include <regex>
#include <iostream>

namespace
{
std::shared_ptr<std::istream> stream(const std::string& text)
{
    return std::make_shared<std::istringstream>(text);
}
}

TEST(EchoTests, EchoesInput)
{
    std::ostringstream out, err;
    EchoCommand(stream("Hello World!")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "Hello World!");
}

TEST(EchoTests, KeepsInnerNewlines)
{
    std::ostringstream out, err;
    EchoCommand(stream("a\nb")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "a\nb");
}

TEST(HeadTests, TakesFirstNLines)
{
    std::ostringstream out, err;
    HeadCommand(1, stream("Hello World!\nHow are you?")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "Hello World!\n");
}

TEST(HeadTests, NLargerThanInput)
{
    std::ostringstream out, err;
    HeadCommand(10, stream("a\nb")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "a\nb");
}

TEST(HeadTests, ZeroLines)
{
    std::ostringstream out, err;
    HeadCommand(0, stream("a\nb")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "");
}

TEST(HeadTests, NegativeNThrows)
{
    std::ostringstream out, err;
    EXPECT_THROW(HeadCommand(-1, stream("a")).execute(std::cin, out, err), SemanticError);
}

TEST(WCTests, CountsWords)
{
    std::ostringstream out, err;
    WCCommand(true, stream("A C++ program is a sequence of text files (typically header and source files) that "
                           "contain declarations. They undergo translation to become an executable program, which "
                           "is executed when the C++ implementation calls its main function.")).execute(
        std::cin, out, err);
    EXPECT_EQ(out.str(), "36");
}

TEST(WCTests, CountsWordsAcrossLinesAndSpaces)
{
    std::ostringstream out, err;
    WCCommand(true, stream("a  b\n c\n")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "3");
}

TEST(WCTests, CountsChars)
{
    std::ostringstream out, err;
    WCCommand(false, stream("ab\ncd")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "5");
}

TEST(TRTests, RemovesMatches)
{
    std::ostringstream out, err;
    TRCommand(stream("Hello World!\nHow are you?"), " ", "").execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "HelloWorld!\nHowareyou?");
}

TEST(TRTests, ReplacesMatches)
{
    std::ostringstream out, err;
    TRCommand(stream("a-b-c"), "-", "+").execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "a+b+c");
}

TEST(FileCommandTests, TouchCreatesFile)
{
    TempFile file("mini_cli_test_touch.txt");
    std::ostringstream out, err;
    TouchCommand(file.path()).execute(std::cin, out, err);
    EXPECT_TRUE(file.exists());
}

TEST(FileCommandTests, TouchExistingFileThrows)
{
    TempFile file("mini_cli_test_touch_existing.txt");
    file.write("x");
    std::ostringstream out, err;
    EXPECT_THROW(TouchCommand(file.path()).execute(std::cin, out, err), SemanticError);
}

TEST(FileCommandTests, RmRemovesFile)
{
    TempFile file("mini_cli_test_rm.txt");
    file.write("x");
    std::ostringstream out, err;
    RMCommand(file.path()).execute(std::cin, out, err);
    EXPECT_FALSE(file.exists());
}

TEST(FileCommandTests, RmMissingFileThrows)
{
    TempFile file("mini_cli_test_rm_missing.txt");
    std::ostringstream out, err;
    EXPECT_THROW(RMCommand(file.path()).execute(std::cin, out, err), OSError);
}

TEST(FileCommandTests, TruncateEmptiesFile)
{
    TempFile file("mini_cli_test_truncate.txt");
    file.write("content");
    std::ostringstream out, err;
    TruncateCommand(file.path()).execute(std::cin, out, err);
    EXPECT_TRUE(file.exists());
    EXPECT_EQ(file.read(), "");
}

TEST(FileCommandTests, TruncateMissingFileThrows)
{
    TempFile file("mini_cli_test_truncate_missing.txt");
    std::ostringstream out, err;
    EXPECT_THROW(TruncateCommand(file.path()).execute(std::cin, out, err), SemanticError);
}

TEST(RedirectionTests, SecondInputRedirectThrows)
{
    EchoCommand echo(nullptr);
    echo.redirectInput(stream("a"));
    EXPECT_THROW(echo.redirectInput(stream("b")), SemanticError);
}

TEST(RedirectionTests, OutputOnlyCommandRejectsInputRedirect)
{
    DateCommand date;
    EXPECT_THROW(date.redirectInput(stream("a")), SemanticError);
}

TEST(RedirectionTests, PlainCommandRejectsAnyRedirect)
{
    TouchCommand touch("x");
    EXPECT_THROW(touch.redirectInput(stream("a")), SemanticError);
    EXPECT_THROW(touch.redirectOutput(std::make_shared<std::ostringstream>()), SemanticError);
}

TEST(OutputCommandTests, DateFormat)
{
    std::ostringstream out, err;
    DateCommand().execute(std::cin, out, err);
    EXPECT_TRUE(std::regex_match(out.str(), std::regex(R"(\d{2}\.\d{2}\.\d{4})"))) << out.str();
}

TEST(OutputCommandTests, TimeFormat)
{
    std::ostringstream out, err;
    TimeCommand().execute(std::cin, out, err);
    // Prefix match: the output currently also carries fractional seconds (e.g. "18:53:02.770729").
    EXPECT_TRUE(std::regex_search(out.str(), std::regex(R"(^\d{2}:\d{2}:\d{2})"))) << out.str();
}

TEST(PromptTests, ChangesPrompt)
{
    std::ostringstream out, err;
    PromptCommand("#").execute(std::cin, out, err);
    EXPECT_EQ(ICommand::getPrompt(), "#");
    PromptCommand("$").execute(std::cin, out, err);
    EXPECT_EQ(ICommand::getPrompt(), "$");
}

TEST(BatchTests, RunsCommandsFromStream)
{
    std::ostringstream out, err;
    BatchCommand(stream("echo \"mare\"\nwc -c \"mare\"\n")).execute(std::cin, out, err);
    EXPECT_EQ(out.str(), "mare4");
    EXPECT_EQ(err.str(), "");
}
