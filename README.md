# Minishell

> A small Unix shell written in C, inspired by Bash.

## About

Minishell is a Unix shell implementation developed as part of the 42 curriculum.
The project focuses on process management, command parsing, environment handling,
pipes, redirections and signal management.

## Features

- Command tokenization and parsing
- Environment variable expansion
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes and command execution
- Input/output redirections
- Heredocs
- Signal handling
- Interactive mode with command history
- Non-interactive input support
- Memory management and cleanup

## Technologies

- **Language:** C
- **Platform:** Unix / POSIX
- **Libraries:** GNU Readline, custom Libft
- **Build:** Make
- **Testing:** Bash comparison, Valgrind

## Installation

### Requirements

- GCC or Clang
- Make
- GNU Readline

### Build

```bash
git clone git@github.com:lperalta14/minishell.git
cd minishell
make
```
## Usage
Run the shell with:
```bash
./minishell
```
Example:
```bash
minihell> echo "Hello, world!" | grep Hello
Hello, world!
```

## Architecture
```
Input
  │
  ▼
Tokenizer
  │
  ▼
Parser
  │
  ▼
Expander
  │
  ▼
Executor
  ├── Builtins
  ├── Pipes
  ├── Redirections
  └── Heredocs
```
The project is organized into independent modules for tokenization, parsing, expansion, execution, builtins and utilities.

## Testing

A custom Bash-based test script is included to compare Minishell behaviour
against Bash across commands, quotes, variables, pipes, redirections and
other edge cases.

Run the test suite with:
```bash
./tests/test_all_cases.sh
```
Valgrind can also be used to inspect memory management:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

## Authors

**Luis Peralta** · [GitHub](https://github.com/lperalta14) · [LinkedIn](www.linkedin.com/in/lperaltamuñoz)

Maria Sedeño · [GitHub](https://github.com/casimarasn) · 42 Málaga
