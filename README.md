
# Minishell Project

## Index

- [Minishell Project](#minishell-project)
  - [Index](#index)
  - [Introduction](#introduction)
  - [Project Overview](#project-overview)
    - [Key Features:](#key-features)
  - [Technologies Used](#technologies-used)
  - [Project Difficulty](#project-difficulty)
  - [Implementation Details](#implementation-details)
    - [Shell Behavior](#shell-behavior)
    - [Built-in Commands](#built-in-commands)
    - [Redirection and Piping](#redirection-and-piping)
  - [Usage Guide](#usage-guide)
    - [Installation](#installation)
    - [Running the Shell](#running-the-shell)
    - [Exiting the Shell](#exiting-the-shell)
  - [Available Commands](#available-commands)

---

## Introduction

Welcome to the **Minishell project**! This project involves creating a **simple shell** similar to **Bash**. Through this project, you will gain deep insights into how **processes** and **file descriptors** work in **Unix-based systems**. Minishell is designed to offer a journey back to the origins of **command-line interfaces**, allowing you to explore fundamental **IT concepts** and the challenges faced by developers before the advent of **graphical user interfaces**.

## Project Overview

The goal of this project is to build a **functional shell** that can interpret and execute user commands in a **Unix-like environment**. The shell will support basic features such as executing commands, handling **input/output redirection**, managing **pipes**, and expanding **environment variables**. Additionally, the project involves implementing several **built-in commands** to simulate the behavior of a standard shell.

### Key Features:

- **Command execution** based on the **PATH environment variable**.
- **Input/output redirection** and **piping**.
- **Built-in commands** such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signal handling** for interactive command-line behavior (e.g., `ctrl-C`, `ctrl-D`).

## Technologies Used

This project is implemented in **C** and adheres to strict **coding norms** to ensure **reliability** and **maintainability**. Key technologies and libraries include:

- **readline** for **command-line input handling**.
- Standard **C libraries** for **memory management**, **file I/O**, and **process control**.
- **Libft**, a custom **C library**, is used for various **utility functions**.

## Project Difficulty

The **Minishell project** is considered to be of **moderate to high difficulty**. It requires a solid understanding of **process management**, **memory handling**, and **Unix system calls**. Additionally, careful attention to detail is needed to avoid issues like **memory leaks** and **segmentation faults**. The project also demands strict adherence to **coding standards** and efficient management of resources such as **file descriptors** and **environment variables**.

## Implementation Details

### Shell Behavior

The shell displays a **prompt** and waits for user input. It processes the input to:

- **Parse** and **interpret** commands.
- Handle **quoted strings** and **special characters**.
- Implement **redirections** and **pipelines**.

### Built-in Commands

The shell includes several **built-in commands** that are executed internally rather than by spawning new processes. These include:

- `echo`: Outputs text to the terminal with an optional `-n` flag.
- `cd`: Changes the current directory.
- `pwd`: Prints the current working directory.
- `export`: Sets environment variables.
- `unset`: Removes environment variables.
- `env`: Displays the current environment variables.
- `exit`: Exits the shell.

### Redirection and Piping

The shell supports standard **input** and **output redirection** using `>`, `<`, `>>`, and `<<`. Redirection allows commands to read input from a file or write output to a file. **Piping** allows the output of one command to be used as the input to another, using the **pipe** `|` operator.

## Usage Guide

### Installation

1. **Clone** the repository to your local machine.
2. **Navigate** to the project directory.
3. **Compile** the project using the following command:

```bash
make
```

This will generate the `minishell` executable.

### Running the Shell

To start the shell, simply run the following command:

```bash
./minishell
```

You will be greeted with a **prompt** where you can start entering commands.

### Exiting the Shell

To exit the shell, use the `exit` command or press `ctrl-D`.

## Available Commands

The following **built-in commands** are available in **Minishell**:

- **echo**: Prints text to the terminal. Usage: `echo [-n] [string ...]`
- **cd**: Changes the current directory. Usage: `cd [directory]`
- **pwd**: Displays the current working directory.
- **export**: Sets environment variables. Usage: `export [variable=value]`
- **unset**: Removes environment variables. Usage: `unset [variable]`
- **env**: Displays all environment variables.
- **exit**: Exits the shell. Usage: `exit [status]`
