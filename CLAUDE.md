# mini-cli

A small interactive shell-like interpreter in C++23, written as a university OO1 (ETF) assignment. It reads lines, tokenizes them, parses them into a pipeline of commands, and executes them. Code comments, some error messages, and commit messages are in Serbian; identifiers are in English.

## Build & test

CMake (>= 4.1), no wrapper scripts. GoogleTest is fetched via `FetchContent` (needs network on first configure).

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target main    # the CLI
cmake --build cmake-build-debug --target tests   # gtest binary
./cmake-build-debug/tests
```

- All sources are listed explicitly in `SRC` in `CMakeLists.txt` and built into the `mini-cli` OBJECT library, shared by `main` and `tests`. **Every new `.cpp`/`.h` must be added there.**
- `cmake-build-debug`, `.idea`, `.clang-format` are gitignored.

## Architecture

Pipeline per input line (`Program::run` in `Program/Program.cpp`):

```
line (truncated to 512 chars)
  -> Lexer::tokenizeLine      Parsing/Lexer.*   -> std::vector<Token>
  -> Parser::parseLine        Parsing/Parser.*  -> Pipeline { vector<CommandCall> }
  -> Executor::executePipeline Executor/Executor.*
```

- **Token** (`Parsing/Token`): type is `Normal`, `Quoted` (`"..."`), `Option` (`-x`), `OptionQuoted` (`-"..."`), or `Operator` (`|`, `<`, `>`, `>>`). The Lexer only allows `[A-Za-z0-9_.-]`, whitespace and `| < > "` outside quotes; anything else is a `LexicalError`.
- **Parser** splits on `|`, takes the first token of each segment as the command name, handles `<`, `>`, `>>` redirections (opens the files immediately as `ifstream`/`ofstream`), and passes the remaining argument tokens to the command's factory.
- **Factories** (`Factories/`): one `IFactory` subclass per command. Validates the argument tokens and builds the `ICommand`. `IFactory::createIn(token)` turns a `Normal` token into a file stream and a `Quoted` token into an `istringstream`.
- **Registry** (`Factories/Registry`): singleton name -> `IFactory*` map. Each factory registers itself in its constructor, and a file-scope `static XFactory g_xFactory;` in the `.cpp` instantiates it. Unknown name throws `UnknownCommandError`.
- **Executor**: runs commands in order; for pipes, command *i*'s output is captured into an `ostringstream` and fed to command *i+1* as an `istringstream` (fully buffered, not streaming).
- **Commands** (`Commands/`): derive from `ICommand` with `execute(inDefault, outDefault, err)`. Streams are resolved via `getInputStream()`/`getOutputStream()` (redirect if set, else the default).
  - `ICommand` base: redirecting input/output throws `SemanticError`.
  - `IInputOutputCommand` (`echo`, `wc`, `head`, `tr`): allows input and output redirection.
  - `IOutputCommand` (`time`, `date`, `batch`): allows output redirection only.
  - Plain `ICommand` (`touch`, `rm`, `truncate`, `prompt`): no redirection.
  - Redirect-allowed classes permit setting a redirect once; a second one falls through to the base class and throws.
- **Errors** (`Errors/`): all derive from `Error` (`what()` returns the prefixed message): `LexicalError` (prints the line with a `^` caret), `SyntaxError`, `SemanticError`, `OSError`, `UnknownCommandError`. `Program::run` catches `std::exception` per line and writes `what()` to `err`.
- `BatchCommand` runs a file/quoted string as a script by calling `Program::run` recursively with that stream as the command source.
- The prompt is a static string on `ICommand` (default `$`), changed by `prompt`. `Program::run` prints it only when the command stream is `std::cin`.

## Adding a command

1. `Commands/.../XCommand.{h,cpp}` deriving from the right base (see redirection rules above).
2. `Factories/XFactory.{h,cpp}`: header constructor calls `Registry::registerFactory("x", this)`; `.cpp` has `static XFactory g_xFactory;` and `create()` that validates tokens and throws `SyntaxError` on bad count/type.
3. Add all four files to `SRC` in `CMakeLists.txt`.
4. Add tests in `Tests/CommandTests.cpp`.

## Known state / gotchas

- Tests (`Tests/`, 50 gtest cases): `CommandTests` (commands built directly), `LexerTests`, `ParserTests`, `ProgramTests` (end to end via `Program::run` with string streams). New test files must be added to the `tests` target in `CMakeLists.txt`.
- The Lexer rejects `/` outside quotes, so tests that go through it use plain relative file names (see `TempFile` in `Tests/TestUtils.h`, which deletes its file on destruction). Operators (`|`, `<`, `>`, `>>`) must be separated from words by whitespace.
- `time` prints fractional seconds (`18:53:02.770729`); `TimeTests` only matches the `HH:MM:SS` prefix.
- `main.cpp` calls `Program::run(std::cin, std::cin, std::cout, std::cerr)`: commands and data input share `std::cin`.
- Executor reads the whole previous stage's output before starting the next one.

## Conventions

- Style: 4-space indent, Allman braces for classes/functions/blocks, `m_` member prefix, header guards `CLI_*_H`, `[[nodiscard]]` on getters, trivial method bodies defined `inline` at the bottom of headers.
- Prefer throwing the existing `Error` subclasses over printing; error text goes through `err`.
