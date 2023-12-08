/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 05:55:00 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 22:15:39 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Sub Libraried
# include "defines.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <MiniBuiltins.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <vars.h>

// syntax error msg;
# define PIPE_SYNTAX_ERROR "Error: syntax error near unexpected token `|'\n"
# define IN_SYNTAX_ERROR "Error: syntax error near unexpected token `<'\n"
# define OUT_SYNTAX_ERROR "Error: syntax error near unexpected token `>'\n"

# define SIG_STATE_MAIN 0
# define SIG_STATE_PARENT 1
# define SIG_STATE_CHILD 2
# define SIG_STATE_CHILD_BUILTIN 3
# define SIG_STATE_HD_CHILD 4
# define SIG_STATE_IGNORE 5

# define SIGNAL_NEW_LINE 1
# define SIGNAL_EXIT_HD 2

// # define info(msg, color) printf("%s%d%s : %s[%s]%s\n", MAG, getpid(), RESET,
	// color, msg, RESET);

extern int	g_signal_status;

/*
 * -----------------------------------------------------------------------
 * -                                                                     -
 * -                                                                     -
 * -                            SYNTAX UTILS                             -
 * -                                                                     -
 * -                                                                     -
 * -----------------------------------------------------------------------
 */
void		err_print(char *msg);
void		skip_string_skip(char *in, int *i, t_shell *sh);
bool		pipe_analizer(char *in, int *i, t_shell *sh);
bool		redi_ana(char *in, int *i, t_shell *sh);

/*
 * -----------------------------------------------------------------------
 * -                                                                     -
 * -                                                                     -
 * -                            SYNTAX FUNCS                             -
 * -                                                                     -
 * -                                                                     -
 * -----------------------------------------------------------------------
 */
void		syntax_pipe(char *in, int *i, t_shell *sh);
void		syntax_notsupported(char *in, int *i, t_shell *sh);
void		syntax_redirection(char *in, int *i, t_shell *sh);
void		syntax_quotes(char *input, int i, int *flag, t_shell *sh);
void		switch_caracters(char **ptr);
void		remove_quotes(char *str);
void		close_redi(t_cmds *node);
int			free_split(char **split, int ret);
void		clean_commands(t_cmds **cmds);
t_cmds		*ft_buildlst(char *elements, t_shell *sh);
t_cmds		*ft_lstpos(t_cmds *cmds);
t_cmds		*_create_node(char *cmd);
t_cmds		*_add(char *cmd_line, t_cmds **head, t_shell *sh);

/*
 * -----------------------------------------------------------------------
 * -                                                                     -
 * -                                                                     -
 * -                             UTILS FUNCS                             -
 * -                                                                     -
 * -                                                                     -
 * -----------------------------------------------------------------------
 */
void		clean_redirection(t_redirections **head);
void		redirection(t_cmds *node, t_shell *sh);
void		redirect(t_cmds *node);
bool		isbuiltin(t_cmds *cmd);
int			clean(t_shell *sh, bool _exit, int status, char *msg);
void		ft_ml_envadd_back(t_env **lst, t_env *new);
t_env		*ft_env_add(char *str, int has_equal);
int			ft_env_delete(t_env **env);
t_env		*set_env(char **envp);
void		parse(t_cmds *node, t_shell *sh);
void		exec_ptr_chooser(t_cmds *node);
void		pipeline(t_cmds *node);
void		setup_fd_for_next_fork(t_cmds *head);
char		*varlib_execute(char *s, t_shell *h);
/*
 * -----------------------------------------------------------------------
 * -                                                                     -
 * -                                                                     -
 * -                 DOUBLE POINTER CHAR MANIPULATION                    -
 * -                                                                     -
 * -                                                                     -
 * -----------------------------------------------------------------------
 */

void		split_str_del(char **arr, int index);
void		split_str_move(char ***src, int src_index, char ***dest,
				int dest_index);
void		split_str_replace(char **str, int index, char *new);
char		**split_str_copy(char **src);
void		heredoc(t_cmds *node, char *delimiter, int fdo);
int			execution_part(t_shell *sh);
void		redirection(t_cmds *node, t_shell *sh);

/*
 * -----------------------------------------------------------------------
 * -                                                                     -
 * -                                                                     -
 * -                               SIGNALS                               -
 * -                                                                     -
 * -                                                                     -
 * -----------------------------------------------------------------------
 */
void		ft_ml_sigdefault(int fork);
void		handle_quit(int sig, t_shell *sh);
void		handle_sign(int sig, t_shell *sh);
void		handle_quit_fork(int sig, t_shell *sh);

void		ft_syntax_checker(char *input, t_shell *sh);
void		quote_delete_str(char **input, char c, t_shell *sh);
void		syntax_report(char *error, char *input, int size, t_shell *sh);
void		prompt(t_shell *shell);

// Redirection Functions
bool		t_redirection_has_hd(t_redirections *lst);
// Runner Functions.
void		wait_for_child(t_shell *sh, int **processlist, int *process);
void		run_parrent(t_cmds *node, int **ps);
void		update_signal_for_child(t_cmds *cmd);
void		wait_case_heredoc(t_shell *sh, t_cmds *cmd, int **ps, int *p);
#endif
