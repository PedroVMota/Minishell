/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:54:28 by pvital-m          #+#    #+#             */
/*   Updated: 2023/09/01 10:52:05 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum token_status
{
	ENV_MODE_TOKEN,
	ENV_MODE_QUOTE,
	ENV_MODE_DQUOTE,
}						t_mode;

typedef struct s_env
{
	char				*var;
	char				*value;
	int					var_len;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd
{
	int pipe[2];				// pipe;
	int red[2]; 			// in case there is a redirection token

	char				**cmd; // command and arguments
	struct s_cmd	*prev; 
	struct s_cmd	*next;
}						t_cmds;

typedef struct s_shell
{
	int					exit;
	int					hd;
	int					stop;
	t_env				*env;
}						t_shell;

# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_PATHS "Error: Split Path variable\n"
# define ERR_FORK "Error: fork failed\n"
# define ERR_PIPE "Error: pipe failed\n"
# define ERR_DUP2 "Error: dup2 failed\n"
# define ERR_OPEN "Error: open failed\n"
# define ERR_CLOSE "Error: close failed\n"
# define ERR_EXECVE "Error: execve failed\n"
# define ERR_CD "Error: cd failed\n"
# define ERR_CHDIR "Error: chdir failed\n"
# define ERR_GETCWD "Error: getcwd failed\n"
# define ERR_ENV "Error: env failed\n"
# define ERR_EXIT "Error: exit failed\n"
# define ERR_UNSET "Error: unset failed\n"
# define ERR_EXPORT "Error: export failed\n"
# define ERR_EXPORT_INVALID_IDENTIFIER "not a valid identifier\n"
# define ERR_EXPORT_TOO_MANY_ARGUMENTS "Error: to many arguments\n"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_GENERAL_ERROR 2
# define EXIT_COMMAND_NOT_EXECUTABLE 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_INVALID_ARGUMENT 128
# define EXIT_INTERRUPTED_BY_CTRL_C 130
# define EXIT_STATUS_OUT_OF_RANGE 255

# define TOKEN_DQUOTE '\1'
# define TOKEN_QUOTE '\2'
# define TOKEN_PIPE '\3'
# define TOKEN_SPACE '\4'
# define TOKEN_SEMI_COLOM '\5'
# define TOKEN_OUT '\6'
# define TOKEN_IN '\7'

#endif