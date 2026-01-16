cmake_minimum_required(VERSION 4.1)
project(CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(CLI
        main.cpp
        commands/Command.h
        Parsing/Argument.h
        commands/EchoCommand.cpp
        commands/EchoCommand.h
        errors/Errors.h
        Parsing/Lexer.cpp
        Parsing/Lexer.h
        commands/CommandFactory.cpp
        commands/CommandFactory.h
        Parsing/Parser.cpp
        Parsing/Parser.h
        commands/TimeCommand.cpp
        commands/TimeCommand.h
        commands/DateCommand.cpp
        commands/DateCommand.h
        commands/TouchCommand.cpp
        commands/TouchCommand.h
        commands/WCCommand.cpp
        commands/WCCommand.h
        Program/Executor.h
        Program/Program.cpp
        Program/Program.h
        Program/Executor.cpp
)
