cmake_minimum_required(VERSION 4.1)
project(CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(cli
        main.cpp
        Commands/Command.h
        Parsing/Token.h
        Commands/InputOutputCommands/EchoCommand.cpp
        Commands/InputOutputCommands/EchoCommand.h
        errors/Errors.h
        Parsing/Lexer.cpp
        Parsing/Lexer.h
        CommandFactories/CommandFactory.cpp
        CommandFactories/CommandFactory.h
        Parsing/Parser.cpp
        Parsing/Parser.h
        Commands/OutputCommands/TimeCommand.cpp
        Commands/OutputCommands/TimeCommand.h
        Commands/OutputCommands/DateCommand.cpp
        Commands/OutputCommands/DateCommand.h
        Commands/TouchCommand.cpp
        Commands/TouchCommand.h
        Commands/InputOutputCommands/WCCommand.cpp
        Commands/InputOutputCommands/WCCommand.h
        Program/Executor.h
        Program/Program.cpp
        Program/Program.h
        Program/Executor.cpp
        Parsing/Token.cpp
        Commands/OutputCommands/BatchCommand.cpp
        Commands/OutputCommands/BatchCommand.h
        Commands/OutputCommands/OutputCommand.h
        Commands/InputOutputCommands/IInputOutputCommand.h
)
