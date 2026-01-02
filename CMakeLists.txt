cmake_minimum_required(VERSION 4.1)
project(CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(CLI
        main.cpp
        commands/Command.h
        parser/Argument.h
        commands/EchoCommand.cpp
        commands/EchoCommand.h
        errors/Errors.h
        Lexer.cpp
        Lexer.h
        commands/CommandFactory.cpp
        commands/CommandFactory.h
        parser/Parser.cpp
        parser/Parser.h
        commands/TimeCommand.cpp
        commands/TimeCommand.h
        commands/DateCommand.cpp
        commands/DateCommand.h
)
