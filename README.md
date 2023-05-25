# Shell Project
This is a simple shell program implemented in C. It provides a basic command-line interface where users can execute commands, navigate directories, set/unset environment variables, and perform other common shell operations.

# Features
* Display a prompt and wait for user commands.
* Execute common shell commands (ls, cd, env, etc.).
* Handle errors and display appropriate error messages.
* Set and unset environment variables.
* Change the current directory (cd command).
* Support for built-in commands: exit, env, setenv, unsetenv.
* Handle end-of-file condition (Ctrl+D) to exit the shell.
# Getting Started
To build and run the shell program, follow these steps:

* Clone the repository or download the source code.
* Navigate to the project directory.
* Compile the source code using a C compiler:
  gcc *.c
* Run the compiled executable:
  ./a.out
* The shell program will start, and you will see a prompt (Shell >) indicating that it is ready to accept commands.

# Usage
The shell program supports common shell commands and built-in commands. Here are some examples:

* Execute a command:
 `Shell > ls`

* Change the directory:
  `Shell > cd /path/to/directory`

* Set an environment variable:
 `Shell > setenv VARIABLE VALUE`

* Unset an environment variable:
  `Shell > unsetenv VARIABLE`

* Print the current environment:
  `Shell > env`
* Exit the shell:
  `Shell > exit`

# Contributing
Contributions to the project are welcome! If you find any issues or have ideas for improvements, feel free to open an issue or submit a pull request.

