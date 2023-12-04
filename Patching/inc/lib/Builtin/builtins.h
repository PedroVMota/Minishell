#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"
# include "minishell.h"
# include "stdbool.h"


int is_valid_fd(int fd);
int *set_dups(t_cmds *node);
int permission_tester(t_cmds *head, int arr[]);
void	remove_part_str(char **str, const char *remove);
void	update_pwd_values(t_env **env, char *oldpwd, char *pwd);
char	*get_pwd_from_list(t_env *env);
int		check_repetition(t_env *new, t_env **env);
bool	file_descriptor_in(t_cmds *node);
bool	file_descriptor_out(t_cmds *node);
int	check_nothing(t_cmds *node);

/**
 * Chooses which standard function to execute based on the command name.
 *
 * @param cmd The command to execute.
 * @return The exit status of the executed command.
 */
int		standard_choiser(t_cmds *cmd);

/**
 * Displays the environment variables.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_env(t_cmds *node);

/**
 * Displays the arguments passed to it.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_echo(t_cmds *node);

/**
 * Changes the current working directory.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_cd(t_cmds *node);

/**
 * Displays the current working directory.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_pwd(t_cmds *node);

/**
 * Adds or modifies environment variables.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_export(t_cmds *node);

/**
 * Deletes environment variables.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_unset(t_cmds *node);

/**
 * Exits the shell.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_exit(t_cmds *node);

/**
 * Executes a command.
 *
 * @param node The command node containing the arguments.
 * @return The exit status of the executed command.
 */
int		ft_exec(t_cmds *node);
#endif