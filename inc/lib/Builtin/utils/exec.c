/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/01 15:51:23 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ShowSingleCommand(t_cmds *cmd);

// Create a function that will search the redirection.
// if there is an an output but the redirection return a
// error then the current process must not execute.

bool	permission_w(t_cmds *cmd)
{
	if (access(cmd->args[0], W_OK) == -1)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Permission denied\n", 21);
		cmd->sh->exit = 126;
		return true;
	}
	return (false);
}
bool	permission_r(t_cmds *cmd)
{
	if (access(cmd->args[0], R_OK) == -1)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": No such file or directory\n", 29);
		cmd->sh->exit = 127;
		return true;
	}
	return (false);
}

bool	permission_x(t_cmds *cmd)
{
	if (access(cmd->args[0], X_OK) == -1)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Permission denied\n", 21);
		cmd->sh->exit = 126;
		return true;
	}
	return (false);
}

bool	permission_f(t_cmds *cmd)
{
	if (access(cmd->args[0], F_OK) == -1)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": No such file or directory\n", 29);
		cmd->sh->exit = 127;
		return true;
	}
	return (false);
}

int	ft_exec(t_cmds *node)
{
	// standard_choiser(node);
	if (permission_f(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (permission_r(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (permission_x(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (!node->shouldrun)
		clean(node->sh, true, node->sh->exit, NULL);
	if (execve(node->args[0], node->args, node->sh->envp))
	{
		perror(node->args[0]);
		clean(node->sh, true, errno, NULL);
	}
	return (0);
}
