# Resources
https://harm-smits.github.io/42docs/projects/minishell

# Minishell
*This project has been created as part of the 42 curriculum by anegorov et domingo.*

## Description

Minishell is a Unix shell implemented in C as part of the 42 curriculum. The goal of this project is to recreate a simplified version of a shell like bash, including parsing, execution, pipes, redirections, environment variables, built-in commands, and process management.

This project helps understand how a shell works internally and how it interacts with the operating system through system calls such as fork, execve, pipe, dup2, and others.

## Instructions

### Compilation

Run:

make

This will generate the executable:

./minishell

### Execution

Run the shell:

./minishell

You will get an interactive prompt similar to bash.

### Features

- Execution of binaries from PATH
- Built-in commands:
  - cd
  - echo
  - pwd
  - export
  - unset
  - env
  - exit
- Pipes |
- Redirections:
  - < input
  - > output
  - >> append
  - << heredoc
- Environment variable expansion ($VAR)
- Quotes:
  - single quotes (literal)
  - double quotes (with expansion)
- Signal handling:
  - Ctrl+C
  - Ctrl+D
  - Ctrl+\
- Wildcards * (bonus)

## Bonus

### Wildcards

Wildcard * is supported in the current working directory.

Example:

ls *.c

This expands to all .c files in the current directory.

## Resources

### Documentation

https://man7.org/linux/man-pages/
https://www.gnu.org/software/bash/manual/
https://www.gnu.org/software/libc/manual/
https://pubs.opengroup.org/onlinepubs/9699919799/

### Tutorials

https://tldp.org/LDP/Bash-Beginners-Guide/html/
https://www.geeksforgeeks.org/making-linux-shell-in-c/
https://stackoverflow.com/questions/tagged/shell

### AI Usage

AI (ChatGPT) was used for:

- Structuring README according to 42 requirements
- Improving clarity of explanations
- Formatting documentation
- Helping describe architecture (lexer, parser, executor, expander)
- Debugging conceptual issues (pipes, parsing, execution flow)

All final code and implementation decisions were made by the author.

## Technical Overview

The project is divided into:

- Lexer (tokenization)
- Parser (command building)
- Expander (variables + wildcards)
- Executor (process execution)

System calls used:

fork
execve
pipe
dup2
waitpid
open
read
write
chdir
getcwd


