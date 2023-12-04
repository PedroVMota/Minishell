
# Minishell

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193606493-2969e425-6bad-44ce-97af-89fec62bee22.gif" width=500>
    </picture>
  </a>
</p>

*A mini recreation of bash.  Implementing previously learned concepts like file descriptors and processes.  Made with [Pedro Mota](https://github.com/pedrovmota).*

## Table of Contents
- [The Challenge](#the-challenge)
  - [What Is Bash and How Does It Work?](#what-is-bash-and-how-does-it-work)
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
    #example 1.
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

I think you are getting there. here is something what will help more later

### Todo:



