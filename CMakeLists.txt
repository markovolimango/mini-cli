cmake_minimum_required(VERSION 4.1)
project(CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(CLI
        main.cpp
        Commands/Base/Command.h
        Parsing/Token.h
        Commands/EchoCommand.cpp
        Commands/EchoCommand.h
        errors/Errors.h
        Parsing/Lexer.cpp
        Parsing/Lexer.h
        Commands/Factory/CommandFactory.cpp
        Commands/Factory/CommandFactory.h
        Parsing/Parser.cpp
        Parsing/Parser.h
        Commands/TimeCommand.cpp
        Commands/TimeCommand.h
        Commands/DateCommand.cpp
        Commands/DateCommand.h
        Commands/TouchCommand.cpp
        Commands/TouchCommand.h
        Commands/WCCommand.cpp
        Commands/WCCommand.h
        Program/Executor.h
        Program/Program.cpp
        Program/Program.h
        Program/Executor.cpp
        Commands/Base/Command.cpp
        Parsing/Token.cpp
        Commands/BatchCommand.cpp
        Commands/BatchCommand.h
)
