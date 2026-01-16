#ifndef CLI_ERROR_H
#define CLI_ERROR_H

#include <stdexcept>
#include <string>

class Error : public std::runtime_error
{
public:
    explicit Error(const std::string& message) :
        std::runtime_error(message)
    {
    }
};

class LexicalError : public Error
{
public:
    explicit LexicalError(const std::string& message) :
        Error("Leksicka greska: " + message)
    {
    }
};

class SyntaxError : public Error
{
public:
    explicit SyntaxError(const std::string& message) :
        Error("Sintaksna greska: " + message)
    {
    }
};

class SemanticError : public Error
{
public:
    explicit SemanticError(const std::string& message) :
        Error("Semanticka greska: " + message)
    {
    }
};

class OSError : public Error
{
public:
    explicit OSError(const std::string& message) :
        Error("OS Greska: " + message)
    {
    }
};


#endif
