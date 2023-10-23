#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void    redirect_funct(void);
int     execute_single_comand(t_shell *sh);
void    remove_part_str(char *str, const char *remove);


int builtins(t_cmds *node);
int builtin_cd(t_cmds *node);
int builtin_export(t_cmds *node);
int builtin_unset(t_cmds *node);
int builtin_env(t_cmds *node);
int builtin_echo(t_cmds *node);
int builtin_pwd();

int standard_choiser(t_cmds *cmd);
int ft_env(t_cmds *node);
#endif