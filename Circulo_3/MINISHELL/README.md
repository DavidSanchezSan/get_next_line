*This project has been created as part of the 42 curriculum by dasanche and egarcia2 (students of 42 Madrid).*

# Minishell

## Description

**Minishell** is a simplified Unix shell written in C, developed as part of the 42 School curriculum.  
The goal of this project is to recreate the core behavior of a Unix shell (similar to Bash) while respecting strict constraints on allowed functions, memory management, and coding style.

The  project focuses on understanding how shells work internally, including:
- process creation and management,
- file descriptors and redirections,
- pipes,
- signal handling,
- environment variables,
- and command parsing.

## Instructions

### Requirements
* Unix-like operating system (Linux or macOS)
* `gcc` or `cc`
* GNU Readline library
* Make

### Compilation
Clone the repository and compile the project using:

`make`

This will produce an executable named minishell.

#### Available Makefile rules:
* `make` or `make all` – compile the project
* `make clean` – remove object files
* `make fclean` – remove object files and the executable
* `make re` – recompile everything

### Execution
Run minishell with:

``./minishell``

You will be presented with an interactive prompt:

``minishell>``

From there, you can execute commands as you would in a regular shell.

### Features
Minishell is a miniature shell program based on Bash that supports:
* Prompt display
* Command history
* Command execution using PATH, relative paths, or absolute paths
* Built-in commands:
    * ``echo`` (with ``-n``)
    * ``cd``
    * ``pwd``
    * ``export``
    * ``unset``
    * ``env``
    * ``exit``
* Pipes (|)
* Redirections:
    * ``<`` input redirection
    * ``>`` output redirection
    * ``>>`` append output redirection
    * ``<<`` heredoc
* Environment variable expansion (``$VAR``)
* Exit status expansion (``$?``)
* Signal handling:
    * ``Ctrl-C`` interrupts the current command and returns to the prompt
    * ``Ctrl-D`` exits the shell
    * ``Ctrl-\`` is ignored in interactive mode

## Resources

### Technical References Used for the Minishell Project

The following resources were used to understand and implement the project:

* [Bash manual](https://www.gnu.org/software/bash/manual/bash.html)

* [Shell Command Language Manual](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

* [Readline Documentation](https://manpagez.com/info/rlman/rlman-6.2/rlman_23.php#Programming-with-GNU-Readline)

* [Advanced Programming in the UNIX Environment – W. Richard Stevens](https://github.com/Lincheng1993/apue/blob/master/Advanced%20Programming%20in%20the%20UNIX%20Environment%203rd%20Edition.pdf)

* [The Linux Programming inTerface A Linux and UNIX® System Programming Handbook – W. Richard Stevens](https://www.bogotobogo.com/Linux/files/the-linux-programming-interface-1.pdf)

* For understanding [processes, signals, and file descriptors](https://www.codequoi.com/en/)

* Linux man pages


### Use of Artificial Intelligence
Artificial Intelligence tools were used responsibly and selectively during the development of this project, in accordance with the 42 guidelines.

Specifically, AI assistance was used for:
* Clarifying Unix concepts (signals, processes, pipes, among others),
* Identifying edge cases and comparing expected behavior with Bash in complex scenarios,
* Detecting and reasoning about potential errors, overflows, and undefined behaviour,
* Asisting with the validation of mathematical logic and algorithm aproach,
* Understanding system limitations and their impact on the shell's behaviour,
* Designing manual tests cases to validate the shell behaviour,
* Improving code readability and documentation.

AI was not used to blindly generate complete solutions. The final implementation reflects our own understanding and learning process, with peer review and manual debugging playing a central role.

---

### Notes
Minishell is not intended to be a full replacement for Bash, but rather a learning-focused reimplementation of its core mechanisms.

---

### Authors
* dasanche
* egarcia2
