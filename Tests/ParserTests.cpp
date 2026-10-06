#include <gtest/gtest.h>
#include "TestUtils.h"
#include "../Parsing/Parser.h"
#include "../Errors/SyntaxError.h"
#include "../Errors/UnknownCommandError.h"

namespace
{
Pipeline parse(const std::string& line)
{
    return Parser::parseLine(Lexer::tokenizeLine(line));
}
}

TEST(ParserTests, EmptyLineIsEmptyPipeline)
{
    EXPECT_TRUE(parse("").commandCalls.empty());
}

TEST(ParserTests, SingleCommand)
{
    auto pipeline = parse("echo \"a\"");
    ASSERT_EQ(pipeline.commandCalls.size(), 1);
    EXPECT_NE(pipeline.commandCalls[0].command, nullptr);
    EXPECT_EQ(pipeline.commandCalls[0].inRedirect, nullptr);
    EXPECT_EQ(pipeline.commandCalls[0].outRedirect, nullptr);
}

TEST(ParserTests, PipeSplitsCommands)
{
    EXPECT_EQ(parse("echo \"a\" | wc -c | wc -w").commandCalls.size(), 3);
}

TEST(ParserTests, RedirectsAreAttachedToTheirCommand)
{
    TempFile in("mini_cli_test_parser_in.txt");
    TempFile out("mini_cli_test_parser_out.txt");
    in.write("x");

    auto pipeline = parse("echo < " + in.path() + " > " + out.path());
    ASSERT_EQ(pipeline.commandCalls.size(), 1);
    EXPECT_NE(pipeline.commandCalls[0].inRedirect, nullptr);
    EXPECT_NE(pipeline.commandCalls[0].outRedirect, nullptr);
}

TEST(ParserTests, UnknownCommandThrows)
{
    EXPECT_THROW(parse("nosuchcommand"), UnknownCommandError);
}

TEST(ParserTests, MissingRedirectTargetThrows)
{
    EXPECT_THROW(parse("echo <"), SyntaxError);
    EXPECT_THROW(parse("echo >"), SyntaxError);
    EXPECT_THROW(parse("echo >>"), SyntaxError);
}

TEST(ParserTests, FactoryRejectsBadArguments)
{
    EXPECT_THROW(parse("wc"), SyntaxError); // missing option
    EXPECT_THROW(parse("wc -x"), SyntaxError); // unknown option
    EXPECT_THROW(parse("touch"), SyntaxError); // missing filename
    EXPECT_THROW(parse("touch \"quoted\""), SyntaxError); // wrong token type
    EXPECT_THROW(parse("echo \"a\" \"b\""), SyntaxError); // too many arguments
}
