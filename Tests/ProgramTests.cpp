#include <gtest/gtest.h>
#include "TestUtils.h"
#include "../Program/Program.h"
#include <sstream>

namespace
{
struct Result
{
    std::string out;
    std::string err;
};

Result run(const std::string& script, const std::string& data = "")
{
    std::istringstream cmds(script), in(data);
    std::ostringstream out, err;
    Program::run(cmds, in, out, err);
    return {out.str(), err.str()};
}
}

TEST(ProgramTests, SingleCommand)
{
    auto r = run("echo \"hello\"");
    EXPECT_EQ(r.out, "hello");
    EXPECT_EQ(r.err, "");
}

TEST(ProgramTests, PipeFeedsNextCommand)
{
    EXPECT_EQ(run("echo \"hello\" | wc -c").out, "5");
}

TEST(ProgramTests, LongPipeline)
{
    EXPECT_EQ(run("echo \"a b c\" | tr -\" \" \"\" | wc -c").out, "3");
}

TEST(ProgramTests, UsesDataStreamWhenNoInputGiven)
{
    EXPECT_EQ(run("wc -w", "one two three").out, "3");
}

TEST(ProgramTests, OutputRedirectAndInputRedirect)
{
    TempFile file("mini_cli_test_program_redirect.txt");
    auto r = run("echo \"hello\" > " + file.path() + "\n"
                 "wc -c < " + file.path());
    EXPECT_EQ(file.read(), "hello");
    EXPECT_EQ(r.out, "5");
    EXPECT_EQ(r.err, "");
}

TEST(ProgramTests, AppendRedirect)
{
    TempFile file("mini_cli_test_program_append.txt");
    run("echo \"a\" > " + file.path() + "\n"
        "echo \"b\" >> " + file.path());
    EXPECT_EQ(file.read(), "ab");
}

TEST(ProgramTests, ErrorGoesToErrAndNextLineStillRuns)
{
    auto r = run("nosuchcommand\necho \"ok\"");
    EXPECT_NE(r.err.find("Unknown command: nosuchcommand"), std::string::npos) << r.err;
    EXPECT_EQ(r.out, "ok");
}

TEST(ProgramTests, RedirectingPlainCommandIsSemanticError)
{
    TempFile file("mini_cli_test_program_plain.txt");
    auto r = run("touch " + file.path() + " > mini_cli_test_unused.txt");
    std::filesystem::remove("mini_cli_test_unused.txt");
    EXPECT_NE(r.err.find("Semantic error"), std::string::npos) << r.err;
}

TEST(ProgramTests, BatchRunsScriptFile)
{
    TempFile script("mini_cli_test_script.txt");
    script.write("echo \"mare\"\nwc -c \"mare\"\n");
    EXPECT_EQ(run("batch " + script.path()).out, "mare4");
}

TEST(ProgramTests, BatchMissingFileReportsOSError)
{
    auto r = run("batch mini_cli_test_no_such_script.txt");
    EXPECT_NE(r.err.find("OS Error"), std::string::npos) << r.err;
}

TEST(ProgramTests, FileLifecycle)
{
    TempFile file("mini_cli_test_program_lifecycle.txt");
    auto r = run("touch " + file.path() + "\n"
                 "echo \"x\" > " + file.path() + "\n"
                 "truncate " + file.path() + "\n"
                 "rm " + file.path());
    EXPECT_EQ(r.err, "");
    EXPECT_FALSE(file.exists());
}
