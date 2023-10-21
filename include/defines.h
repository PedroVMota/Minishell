/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:54:28 by pvital-m          #+#    #+#             */
/*   Updated: 2023/10/01 10:58:41 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
#define DEFINES_H

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum token_status
{
	ENV_MODE_TOKEN,
	ENV_MODE_QUOTE,
	ENV_MODE_DQUOTE,
} t_mode;

typedef struct s_env
{
	char **vars;
	struct s_env *next;
} t_env;

// mode = -1 command
// mode = 0 pipe
// mode = 1 redirect
typedef struct s_cmd
{
	int redirection_type;
	int pipe[2];
	int redirection[2];
	int (*ft_exec)(struct s_cmd *cmd);
	char **args;
	
	struct s_cmd *prev;
	struct s_cmd *next;
} t_cmds;

typedef struct s_shell
{
	int exit;
	int lstsize;
	int hd;
	int stop;
	t_env *env;
} t_shell;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_GENERAL_ERROR 2
#define EXIT_COMMAND_NOT_EXECUTABLE 126
#define EXIT_COMMAND_NOT_FOUND 127
#define EXIT_INVALID_ARGUMENT 128
#define EXIT_INTERRUPTED_BY_CTRL_C 130
#define EXIT_STATUS_OUT_OF_RANGE 255

#define DQUOTE '\1'
#define QUOTE '\2'
#define PIPE '\3'
#define SPACE '\4'
#define SEMI_COLOM '\5'

#define OUTTRUC '\6'
#define OUTAPP '\7'

#define INFILE '\a'
#define HEREDOC '\b'
#define ERRFILE '\f'
#define MASTER '\b'

#endif