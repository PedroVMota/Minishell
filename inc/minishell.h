/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:56:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/11/05 20:06:22 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


// Sub Libraried 

#include <Vars.h>
#include <builtins.h>
#include <defines.h>

#include "defines.h"
#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// syntax error msg;
#define PIPE_SYNTAX_ERROR "Error: syntax error near unexpected token `|'\n"
#define IN_SYNTAX_ERROR "Error: syntax error near unexpected token `<'\n"
#define OUT_SYNTAX_ERROR "Error: syntax error near unexpected token `>'\n"

int clean(t_shell *sh, bool _exit, int status);
char *bash_prompt_replicate(void);
bool permission_tester(t_cmds *head);
int software(t_shell *sh);
// Data Type Manipulation

void heredoc(t_cmds *node, char *delimiter);
void redirection(t_cmds *node, t_shell *sh);

/// @brief Remove an element of a 2D matrix
/// @param arr the list
/// @param index the position that will be removed;
void split_str_del(char **arr, int index);
void split_str_move(char **src, int src_index, char **dest,
					int dest_index);
void split_str_replace(char **str, int index, char *new);
char **split_str_copy(char **src);


// enviroment
void ft_ml_envadd_back(t_env **lst, t_env *new);
t_env *ft_env_add(char *str);
int ft_env_delete(t_env **env);
t_env *set_env(char **envp);

// signals
void ft_ml_sigdefault(void);
void handle_quit(int sig, t_shell *sh);
void handle_sign(int sig, t_shell *sh);

// syntax
void ft_syntax_checker(char *input, t_shell *sh);
void quote_delete_str(char **input, char c, t_shell *sh);
void syntax_report(char *error, char *input, int size, t_shell *sh);
// ui
void prompt(t_shell *shell);

// pase
void parse(t_cmds *node, t_shell *sh);
// AUX

/// @brief Simulate the Bash terminal Syntax
/// @param input the current input
/// @param i int position
/// @param flag arr of sets
void syntax_quotes(char *input, int i, int *flag, t_shell *sh);
void ft_mode_changer_not_printable(char set, t_mode *stat);
/// @brief Replace the the `tokens` for the special caracters
/// @param ptr string that will be modified
void switch_caracters(char **ptr, t_shell *sh);
/// @brief Remove all the Special Quotes
/// @param str ThPe string will be modiefied!
void remove_quotes(char *str);
/// @brief Clean Double pointer
int free_split(char **split, int ret);
/// @brief Frees the memory used by a command list and closes all
/// file descriptors.
/// @param cmds A pointer to the head of the command list.
void clean_commands(t_cmds **cmds);

/// @brief prepare all the meta data information.
/// @param elements The first position of the list
/// @return Return the head position of the lsit
t_cmds *ft_buildlst(char *elements, t_shell *sh);

/// @brief Search the last position of the list
/// @param cmds The first position of the list
/// @return Return the last position of the list
t_cmds *ft_lstpos(t_cmds *cmds);

/// @brief Create a node with everything with the default values
/// @param cmd Will be splitted and give to the nodes->args
/// @return the Allocated Malloc (Free available)
t_cmds *_create_node(char *cmd);

/// @brief Create a node with everything with the default values
/// @param SingleComand Will be splitted and give to the nodes->args
/// @param Head The very first head that will be distribute the done
/// @return Doesn't return nothing. Instead the head will be updated!
t_cmds *_add(char *cmd_line, t_cmds **head, t_shell *sh);

void print_special(char *ptr);
int print_split(char **ptr);
void CommandDisplay(t_cmds *ptr);

#endif
