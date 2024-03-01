
# Minishell

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExa2s2dTdyYmJudGlqYnR1dnp2c3p5MzVsZHptdWI0d2lpd3h5YXIzZiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Y3Bb5MNAtOC4H73qbU/giphy.gif" width=500>
    </picture>
  </a>
</p>

*A mini recreation of bash.  Implementing previously learned concepts like file descriptors and processes.  Made with [Pedro Mota](https://github.com/pedrovmota).*

## Table of Contents
- [The Challenge](#the-challenge)
  - [What Is Bash and How Does It Work?](#what-is-bash-and-how-does-it-work)
  - [Forks and Dups](#Forks-and-Dups)
- [Implementation](#implementation)
  - [The Lexer](#the-lexer)
  - [The Parser](#the-parser)
  - [Builtins](#builtins)
  - [Executor](#executor)
    - [Expander](#expander)
    - [Heredoc](#heredoc)
    - [Single Command](#single-command)
    - [Multiple Commands](#multiple-commands)
  - [Reset](#reset)
- [My Take Away](#my-take-away)
- [Installation](#installation)

## The Challange
This is definitly one of the best/worst project I've ever made, and It wasn't just me, This project in group. The main task of this *Minishell* is to replicate the terminal unix based **Bash**. Do not get wronge with the name **'Mini'** that mean all the possibility of bash running scripts etc... Your task is to make a unix terminal to be able running basic commands, such `ls`, `cat`, `wc` including some builtins `echo`, `pwd`, `unset`, `env`, `cd` ... including 80% of the redirection such as `<`,`>`,`<<`,`>>` and multi command support.

# Example

```bash
    #Bash
    bash $> ls
    Dockerfile  MinishellEn.pdf  docker-compose.yml libft
    src Makefile    README.md   inc minishell

    bash $> ThisCommandShouldNotExit --name .venv
    Bash:   ThisCommandShouldNotExit: No such file or directory 
    bash $> echo $?
    127

    bash $> wc < .gitignore | cat
          10      11      72
```

```bash
    #Minishell
    Minishell $> ls
    Dockerfile  MinishellEn.pdf  docker-compose.yml libft
    src Makefile    README.md   inc minishell

    Minishell $> ThisCommandShouldNotExit --name .venv
    Minishell:   ThisCommandShouldNotExit: No such file or directory 
    Minishell $> echo $?
    127

    Minishell $> wc < .gitignore | cat
          10      11      72
```

# what is bash and how does it work

Bash, which stands for Bourne Again Shell, is a command-line interpreter for the GNU operating system. It is widely used as the default login shell for most Linux distributions and Apple's macOS Mojave and earlier versions. Bash is a Unix shell and command language, and it's an upgrade of the original Bourne Shell (sh).

Here's a basic description of how it works:

1. Command Handling: Bash interprets and executes commands that are entered into the command line interface. These commands can be input directly by the user or read from a file, also known as a shell script.

2. `Builtins`: Bash has a number of built-in commands that it executes directly, without calling external programs. Examples include `cd` to change directories, `echo` to print text, and `exit` to close the shell.

3. `Forking`: When you execute a command in Bash that isn't a builtin, Bash creates a new process to run that command. This is known as forking. The new process, called a child, is a duplicate of the current process, called the parent. The child inherits most of its environment from the parent, but the two processes then run independently.

4. `Redirection`: Bash allows for the redirection of input and output. This means you can take the output of a command and send it to a file or another command, or you can take a file and use it as the input to a command. This is done using the > and < symbols for output and input redirection respectively.

5. Here Documents (`Heredoc`): Bash supports a feature called "here documents" or "`heredocs`". This allows you to use input redirection to feed a command list to an interactive program or a command, such as ftp, `cat`, or ssh. `Heredocs` are often used to write complex multi-line commands. The syntax is `<<` followed by a `delimiter`. All the lines following this until a line containing only the delimiter are redirected as input to the command. For example:

  ```bash 
    #heredoc Example
    # EOF is a Delimiter
    cat << EOF 
    > this is a line.
    > This is another line.
    > EOF
    this is a line.
    This is another line
  ```


# Forks and Dups

In Unix-like operating systems, a fork operation creates a new process. The new `process`, called the child, is an exact copy of the calling process, called the parent, except for a few values that get changed, such as the process ID. This operation is performed by the `fork()` system call.

When a process is forked, both the parent and child processes have their own private address space. This means that the child process gets a separate copy of all the memory that was allocated to the parent process. Any changes made in the child process do not affect the parent process, and vice versa.

However, while the memory space is not shared, `file descriptors` are. `File descriptors` are integer values that the operating system uses to keep track of open files and network connections. If a process opens a file and then forks, both the parent and child processes will share the same file descriptor. This means that they can both read from and write to the same file or network connection.

This sharing of `file descriptors` is one way that processes can communicate with each other, a concept known as Inter-Process Communication (IPC). Other methods of IPC include pipes, sockets, message queues, shared memory, and semaphores.

The common use of Process comunication is used by the function `pipe(ArrofFD)` this sets valid `fd` for a clean comunication between forks;


```C
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  // theses are gonna be `fds`, the porpuse is to make each process to comunicate each other 
  int comunicate[2] = {-1, -1}; //Set both for security reasons.
  int newProcessId = -1; // also for security reasons
  if(pipe(comunicate) == -1 )
  {
    // pipe returns -1 in case of error;
    printf("Error occuring on pipe command\n");
    return 1;
  }
  // Know the FileDescriptors are ready to use it;
  // ---> comunicate[0] is used to read a content only;
  // ---> comunicate[1] is used to write a content only;
  newProcessId = fork();
  if(newProcessId == -1)
  {
    //Error case also;
    printf("Error occuring on fork command\n");
    return 1;
  }

  if(newProcessId == 0)
  {
    // if the new process is 0 that means that we are inside of the child process; otherwise is parent processs.
    write(comunicate[1], "Hello From the child process", 29);

    //closing the filedescriptos because we dont need anymore
    close(comunicate[0]);
    close(comunicate[1]); 
    exit(0); // Destroy the process because we don't want to use anymore.
  }
  else
  {
    //To make sure the content is writen we wait for the child process to finish his works
    waitpid(newProcessId, NULL, 0);
    // after this the child process should be done and we can read the content;
    char contentFromTheFile[99];
    read(comunicate[0], contentFromTheFile, 98);

    // Expected output is "Hello From the child process"
    printf("%s\n", contentFromTheFile); 
    return 0
  }
  return 0;
}
```