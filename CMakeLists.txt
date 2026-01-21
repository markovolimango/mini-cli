cmake_minimum_required(VERSION 4.1)
project(CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(CLI
        main.cpp
        commands/Command.h
        Parsing/Argument.h
        Commands/Types/EchoCommand.cpp
        Commands/Types/EchoCommand.h
        errors/Errors.h
        Parsing/Lexer.cpp
        Parsing/Lexer.h
        commands/CommandFactory.cpp
        commands/CommandFactory.h
        Parsing/Parser.cpp
        Parsing/Parser.h
        Commands/Types/TimeCommand.cpp
        Commands/Types/TimeCommand.h
        Commands/Types/DateCommand.cpp
        Commands/Types/DateCommand.h
        Commands/Types/TouchCommand.cpp
        Commands/Types/TouchCommand.h
        Commands/Types/WCCommand.cpp
        Commands/Types/WCCommand.h
        Program/Executor.h
        Program/Program.cpp
        Program/Program.h
        Program/Executor.cpp
        Commands/Command.cpp
)
