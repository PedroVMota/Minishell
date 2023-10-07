# Minishell

### What is this project?
**Minishell** is a recreation of the terminal [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) where you run specific commands for especific tasks, generally related to the management of the operating system, and is a mandatory project for [42](https://www.42.fr/). This project you have to do it in pairs, and my partner was [**@Omeir**](https://github.com/omeir2404)

### Challenges
The main challenge of this project was to understand how the terminal works, and implement the commands that can be run in the terminal. You can run a Command for example `cat` to display the content inside the terminal or `ls` to list the files in the current directory. Also builtins are implemented, which are commands that are built into the shell itself, and do not require a new process. For example `echo` is a builtin command, and `cd` is also a builtin command. Like said before you can display an information directly on the terminal or you can send the information to a file.

```bash
    echo "Hello World" #This will display Hello World on the terminal

    echo "Hello World" > file.txt #This will display Hello World on the file `file.txt`

    cat file.txt #This will display the file.txt content on the terminal
```

### Our implementation

Generally speaking, there are more or less 4 steps, those are:
1. **Lexer**
2. **Parser**
3. **Expander**
4. **Executor**

[You can read a better explanation here](hhttps://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

#### Data structures

We have a `struct` that will store everything.

```c
typedef enum token_status
{
	ENV_MODE_TOKEN, //token
	ENV_MODE_QUOTE, //quote
	ENV_MODE_DQUOTE, //double quote
}						t_mode;

typedef struct s_env
{
	char				*var; //variable name
	char				*value; //variable value
	int					var_len; //variable name length
	struct s_env		*next; //next variable
}						t_env;

typedef struct s_redirection
{
    int                type; //type of redirection
	char				*infile; //file to read
	char				*outfile; //file to write
    int                 pipe[2]; //pipe
}						t_redirection;

typedef struct s_comands
{
	t_redirection		*redirect; //redirections
	char				**args; //arguments
	struct s_comands	*next; //next command
	void (ft_exec)(struct t_shell, int command)
}						t_commands;

typedef struct s_shell
{
	int					exit;               //exit status
	char				*input;             //input from the terminal
	char				*current_path;      //current path
	char				**paths;            //paths from the environment
	t_env				*env;               //environment variables
	t_commands			*command;           //commands
	int					n_forks;            //number of forks

	struct sigaction	control_cgi add ;          //control c signal
	struct sigaction	control_back_slash; //control back slash signal
	struct sigaction	up_arrow            //up arrow signal
	struct sigaction	down_arrow;         //down arrow signal
}						t_shell;
```

The struct enum is quite easy to explain, it will store the type of token that we are reading, if it is a token, a quote or a double quote. I will mainly for parsing. 

The parser is the software component that reads the command line such as "ls -al" and puts it into a data struct called **s_commands** that will store the commands that will be executed.
