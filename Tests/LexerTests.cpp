#include <gtest/gtest.h>
#include "../Parsing/Lexer.h"
#include "../Errors/LexicalError.h"

namespace
{
void expectToken(const Token& token, TokenType type, const std::string& text)
{
    EXPECT_EQ(token.getType(), type);
    EXPECT_EQ(token.getText(), text);
}
}

TEST(LexerTests, EmptyLineHasNoTokens)
{
    EXPECT_TRUE(Lexer::tokenizeLine("   \t ").empty());
}

TEST(LexerTests, TokenTypes)
{
    auto tokens = Lexer::tokenizeLine("echo \"a b\" -n5 -\"x y\" file.txt");
    ASSERT_EQ(tokens.size(), 5);
    expectToken(tokens[0], TokenType::Normal, "echo");
    expectToken(tokens[1], TokenType::Quoted, "a b");
    expectToken(tokens[2], TokenType::Option, "n5");
    expectToken(tokens[3], TokenType::OptionQuoted, "x y");
    expectToken(tokens[4], TokenType::Normal, "file.txt");
}

TEST(LexerTests, Operators)
{
    auto tokens = Lexer::tokenizeLine("a | b < c > d >> e");
    ASSERT_EQ(tokens.size(), 9);
    expectToken(tokens[1], TokenType::Operator, "|");
    expectToken(tokens[3], TokenType::Operator, "<");
    expectToken(tokens[5], TokenType::Operator, ">");
    expectToken(tokens[7], TokenType::Operator, ">>");
}

TEST(LexerTests, IllegalCharactersAllowedInsideQuotes)
{
    auto tokens = Lexer::tokenizeLine("echo \"a/b?!\"");
    ASSERT_EQ(tokens.size(), 2);
    expectToken(tokens[1], TokenType::Quoted, "a/b?!");
}

TEST(LexerTests, UnclosedQuoteThrows)
{
    EXPECT_THROW(Lexer::tokenizeLine("echo \"abc"), LexicalError);
    EXPECT_THROW(Lexer::tokenizeLine("tr -\"abc"), LexicalError);
}

TEST(LexerTests, IllegalCharacterThrows)
{
    EXPECT_THROW(Lexer::tokenizeLine("echo a/b"), LexicalError);
}

TEST(LexerTests, EmptyOptionThrows)
{
    EXPECT_THROW(Lexer::tokenizeLine("wc -"), LexicalError);
}

TEST(LexerTests, ErrorMessageShowsCaret)
{
    try
    {
        Lexer::tokenizeLine("ab#");
        FAIL() << "expected LexicalError";
    }
    catch (const LexicalError& e)
    {
        EXPECT_NE(std::string(e.what()).find("ab#\n  ^"), std::string::npos) << e.what();
    }
}
