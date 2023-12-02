/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/02 17:54:48 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ShowSingleCommand(t_cmds *cmd);
int		permission_checker(t_redirections *node);

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
		return (true);
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
		return (true);
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
		return (true);
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
		return (true);
	}
	return (false);
}

bool	file_descriptor_in(t_cmds *node){
	int	fd;

	fd = -1;
	if (node->prev)
		fd = node->prev->pipe[0];
	if (node->redirection[0] != -1)
		fd = node->redirection[0];
	if (fd == -1)
		return (false);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (true);
	return false;
}

bool	file_descriptor_out(t_cmds *node){
	int	fd;

	fd = -1;
	if (node->next)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	if (fd == -1)
		return (false);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (true);
	return false;
}

int	ft_exec(t_cmds *node)
{
	redirect(node);
	if (permission_f(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (permission_r(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (permission_x(node))
		clean(node->sh, true, node->sh->exit, NULL);
	if (!node->shouldrun)
		clean(node->sh, true, node->sh->exit, NULL);
	if (file_descriptor_in(node))
		return (1);
	if (file_descriptor_out(node))
		return (1);
	if (execve(node->args[0], node->args, node->sh->envp))
	{
		perror(node->args[0]);
		clean(node->sh, true, errno, NULL);
	}
	return (0);
}
