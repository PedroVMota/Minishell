/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:56:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/10/01 09:40:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "defines.h"
#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

extern t_shell g_shell;

// syntax error msg;
#define PIPE_SYNTAX_ERROR "Error: syntax error near unexpected token `|'\n"
#define IN_SYNTAX_ERROR "Error: syntax error near unexpected token `<'\n"
#define OUT_SYNTAX_ERROR "Error: syntax error near unexpected token `>'\n"

bool	permission_tester(t_cmds *head);
int software(t_cmds *head);
// Data Type Manipulation

void heredoc(t_cmds *node, char *delimiter);
void redirection(t_cmds *node);

/// @brief Remove an element of a 2D matrix
/// @param arr the list
/// @param index the position that will be removed;
void split_str_del(char **arr, int index);
void split_str_move(char **src, int src_index, char **dest,
					int dest_index);
void split_str_replace(char **str, int index, char *new);
char **split_str_copy(char **src);
/// @brief Replace the content.
/// @param str The first position of the str
/// @param new_value the new content
/// @param del Is gonna be the content that will be replaced;
/// @return Return the head position of the lsit
char *replace_var(char *str, char *new_value, char *del);
/// @brief Replace the content.
/// @param str The content
/// @return without the variable name
/// @note Norminette Ok!
char *delete(char *str);
/// @brief Replace all the variable depending if exist or not if
/// 	not then the `$VarName` will be removed
/// @param str the string will be modified
void var_replacer(char **str);
/// @brief Check the number of $ that will be inside the string
/// @param str The string that will be searched!
/// @return A integer 32 that will the number of varaible
/// inside the current variable
int variable_counter(char *str);
/// @brief Choose between replace and delete function depending the
/// variabled founded
/// @param ptr the string that will be modified
/// @return the string modified
char *varcheckvalid(char *ptr);

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

void var_replacer(char **str);
// pase
void parse(t_cmds *node);
bool var_state(char *str);
// AUX

/// @brief Simulate the Bash terminal Syntax
/// @param input the current input
/// @param i int position
/// @param flag arr of sets
void syntax_quotes(char *input, int i, int *flag);
void ft_mode_changer_not_printable(char set, t_mode *stat);
/// @brief Replace the the `tokens` for the special caracters
/// @param ptr string that will be modified
void switch_caracters(char *ptr);
/// @brief Remove all the Special Quotes
/// @param str The string will be modiefied!
void remove_quotes(char *str);
/// @brief Clean Double pointer
void free_split(char **split);
/// @brief Frees the memory used by a command list and closes all
/// file descriptors.
/// @param cmds A pointer to the head of the command list.
void clean_commands(t_cmds **cmds);

/// @brief prepare all the meta data information.
/// @param elements The first position of the list
/// @return Return the head position of the lsit
t_cmds *ft_buildlst(char *elements);

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
t_cmds *_add(char *cmd_line, t_cmds **head);

void print_special(char *ptr);
int print_split(char **ptr);
void CommandDisplay(t_cmds *ptr);

#endif

#define displayerror(err) printf("%s%s%s\n", RED, err, RESET);
