/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:56:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/09/04 09:41:05 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "defines.h"
#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

extern t_shell g_shell;
typedef int64_t t_counter;

#define MEMDEBUG(name, address) printf("%s: %p\n", name, address);
// syntax error msg;
#define PIPE_SYNTAX_ERROR "Error: syntax error near unexpected token `|'\n"
#define IN_SYNTAX_ERROR "Error: syntax error near unexpected token `<'\n"
#define OUT_SYNTAX_ERROR "Error: syntax error near unexpected token `>'\n"

// enviroment
void ft_ml_envadd_back(t_env **lst, t_env *new);
t_env *ft_env_add(char *str);
int ft_env_delete(t_env **env);
t_env *set_env(char **envp);

// signals
void ft_ml_sigdefault(void);
void handle_quit(int sig);
void handle_sign(int sig);

// syntax
void ft_syntax_checker(char *input);
void quote_delete_str(char **input, char c);
void syntax_report(char *error, char *input, int size);
// ui
void prompt(void);

// AUX
void del_quotes(char **input);
void syntax_quotes(char *input, int i, int *flag);
void quote_delete_str(char **input, char c);
t_cmds *ft_build_command(char *input);
void ft_mode_changer_ascii(char set, t_mode *stat);
void ft_mode_changer_not_printable(char set, t_mode *stat);
void switch_caracters(char *ptr);


#endif
