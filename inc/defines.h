/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:32:47 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 20:43:26 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_typeschecker
{
	FILE_NONE,
	FILE_IN_READ,
	FILE_IN_HEREDOC,
	FILE_OUT_TRUNC,
	FILE_OUT_APPEND,
}							t_type;

typedef enum token_status
{
	ENV_MODE_TOKEN,
	ENV_MODE_QUOTE,
	ENV_MODE_DQUOTE,
}							t_mode;

typedef struct s_env
{
	char					**vars;
	struct s_env			*next;
}							t_env;

typedef struct s_redirections
{
	t_type					mode;
	char					**element;
	struct s_redirections	*next;
}							t_redirections;

typedef struct s_cmd
{
	char					**args;
	int						pipe[2];
	int						redirection[2];

	t_redirections			*infiles;
	t_redirections			*outfile;
	int						is_builtin;
	int						saved_stdin;
	int						saved_stdout;
	int						(*ft_exec)(struct s_cmd *node);
	t_redirections			*reds;
	struct s_shell			*sh;
	struct s_cmd			*prev;
	struct s_cmd			*next;

	int						shouldrun;

}							t_cmds;

typedef struct s_shell
{
	// int dups[2]
	char					**envp;
	int						exit;
	int						lstsize;
	int						hd;
	int						stop;

	t_cmds					*cmds;
	t_env					*env;


}							t_shell;

# define EXIT_GENERAL_ERROR 2
# define EXIT_COMMAND_NOT_EXECUTABLE 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_INVALID_ARGUMENT 128
# define EXIT_INTERRUPTED_BY_CTRL_C 130
# define EXIT_STATUS_OUT_OF_RANGE 255

# define DQUOTE '\1'
# define QUOTE '\2'
# define PIPE '\3'
# define SPACE '\4'
# define OUTTRUC '\6'
# define INFILE '\7'
# define HEREDOC '\b'

#endif