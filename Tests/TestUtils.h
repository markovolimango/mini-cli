#ifndef CLI_TESTUTILS_H
#define CLI_TESTUTILS_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

// A file that is removed on destruction. The Lexer rejects '/', so tests that go through
// the Lexer must use a plain file name relative to the working directory.
class TempFile
{
public:
    explicit TempFile(std::string path) : m_path(std::move(path))
    {
        std::filesystem::remove(m_path);
    }

    ~TempFile()
    {
        std::filesystem::remove(m_path);
    }

    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;

    [[nodiscard]] const std::string& path() const { return m_path; }
    [[nodiscard]] bool exists() const { return std::filesystem::exists(m_path); }

    void write(const std::string& content) const
    {
        std::ofstream(m_path) << content;
    }

    [[nodiscard]] std::string read() const
    {
        std::ifstream in(m_path);
        std::stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

private:
    std::string m_path;
};

#endif
