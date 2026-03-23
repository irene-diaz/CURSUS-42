*This project has been created as part of the 42 curriculum by idiaz-ca and abrecio-.*

# Minishell

## Description
Minishell is a simplified shell implementation designed to replicate the basic functionalities of a Unix shell. The goal of this project is to deepen the understanding of process management, file descriptors, and signal handling in a Unix-like environment. It provides a minimalistic yet functional shell that supports command execution, piping, redirections, and built-in commands.

This project is an opportunity to explore the inner workings of a shell, including how it interprets and executes user commands, manages processes, and handles errors. By implementing these features from scratch, the project reinforces knowledge of system calls, memory management, and the C programming language. Additionally, it emphasizes modular design and adherence to coding standards.

## Instructions

### Compilation
To compile the project, ensure you have `make` installed and run the following command in the root directory:

```bash
make
```

This will generate the `minishell` executable in the root directory.

### Execution
To start the shell, execute the following command:

```bash
./minishell
```

Once inside the shell, you can execute commands just as you would in a standard Unix shell. For example:

```bash
ls -l | grep minishell > output.txt
```

### Features
- **Command Execution**: Execute system commands with arguments, such as `ls`, `echo`, or `cat`.
- **Input/Output Redirections**: Redirect input and output using operators like `>`, `<`, and `>>`.
- **Piping**: Chain multiple commands together using the pipe operator `|`.
- **Built-in Commands**:
  - `cd`: Change the current directory.
  - `echo`: Print text to the standard output.
  - `pwd`: Display the current working directory.
  - `export`: Set environment variables.
  - `unset`: Remove environment variables.
  - `env`: Display all environment variables.
  - `exit`: Exit the shell.
- **Signal Handling**: Gracefully handle signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- **Error Handling**: Provide informative error messages for invalid commands or syntax.
- **Environment Management**: Maintain and modify the shell's environment variables.
- **Heredoc Support**: Handle here-document syntax for input redirection.

### Cleaning
To clean up object files and the executable, use:

```bash
make fclean
```

### Technical Decisions
- **Memory Management**: The project uses a custom memory management system to allocate and free memory efficiently. This ensures that memory leaks are avoided and resources are properly managed.
- **Modular Design**: The codebase is divided into logical modules, such as the tokenizer, parser, executor, and built-ins, to ensure maintainability and readability.
- **Norminette Compliance**: The code adheres to the 42 Norminette, ensuring consistency and readability.
- **Error Handling**: Comprehensive error handling is implemented to provide meaningful feedback to the user and ensure the shell remains stable under unexpected conditions.
- **Signal Handling**: Signals like `SIGINT` and `SIGQUIT` are managed to provide a seamless user experience, mimicking the behavior of a real shell.

## Resources

### Documentation
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html): Used for handling user input.
- [POSIX Specification](https://pubs.opengroup.org/onlinepubs/9699919799/): Reference for system calls and shell behavior.
- [Linux Programmer's Manual](https://man7.org/linux/man-pages/): Comprehensive documentation for Linux system calls and utilities.

### Tutorials
- [Beej's Guide to C Programming](https://beej.us/guide/bgc/): A beginner-friendly guide to C programming.
- [Unix Shell Programming](https://www.tldp.org/LDP/abs/html/): Advanced Bash-Scripting Guide.
- [Learn C the Hard Way](https://learncodethehardway.org/c/): A hands-on approach to learning C programming.
- [Understanding Unix Processes](https://www.geeksforgeeks.org/processes-in-unix/): A detailed explanation of process management in Unix.

### Use of AI
AI assistance was utilized for:
- Refactoring code to comply with the 42 Norminette.
- Debugging and optimizing the Makefile to prevent unnecessary relinking.
- Structuring and improving the README.md file.
- Providing suggestions for modularizing the codebase and improving maintainability.
- Generating examples and explanations for complex shell features.

## Examples
Here are some examples of commands you can run in Minishell:

```bash
# List files in the current directory
ls -l

# Redirect output to a file
echo "Hello, World!" > hello.txt

# Chain commands with pipes
cat file.txt | grep "pattern" | wc -l

# Use built-in commands
export MY_VAR="42"
echo $MY_VAR
unset MY_VAR

# Use heredoc syntax
cat << EOF
This is a heredoc example.
EOF
```