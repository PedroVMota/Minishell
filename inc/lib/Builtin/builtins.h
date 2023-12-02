/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:52:42 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:01:21 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"
# include "minishell.h"
# include "stdbool.h"

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