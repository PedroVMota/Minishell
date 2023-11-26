/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/26 19:12:11 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int get_in(t_cmds *node)
// {
// 	int fd;

// 	fd = -1;
// 	if (node->prev && node->prev->pipe[0] != -1)
// 		fd = node->prev->pipe[0];
// 	if (node->redirection[0] != -1)
// 		fd = node->redirection[0];
// 	return (fd);
// }

// int get_ou(t_cmds *node)
// {
// 	int fd;

// 	fd = -1;
// 	if (node->next && node->pipe[1] != -1)
// 		fd = node->pipe[1];
// 	if (node->redirection[1] != -1)
// 		fd = node->redirection[1];
// 	return (fd);
// }

// static void end_endpoits(t_cmds *cmd, int fdi, int fdo)
// {
// 	if (cmd->prev)
// 	{
// 		close(cmd->prev->pipe[0]);
// 	}
// 	if (cmd->pipe[0] != -1)
// 		close(cmd->pipe[0]);
// 	if (cmd->pipe[1] != -1)
// 		close(cmd->pipe[1]);
// 	if (cmd->redirection[0] != -1)
// 		close(cmd->redirection[0]);
// 	if (cmd->redirection[1] != -1)
// 		close(cmd->redirection[1]);
// 	if (fdi != -1)
// 		close(fdi);
// 	if (fdo != -1)
// 		close(fdo);
// }

// int standard_choiser(t_cmds *cmd)
// {
// 	int fdi = -1;
// 	int fdo = -1;

// 	if (fdi != -1)
// 	{
// 		dup2(fdi, STDIN_FILENO);
// 		close(fdi);
// 	}
// 	if (fdo != -1)
// 	{
// 		dup2(fdo, STDOUT_FILENO);
// 		close(fdi);
// 	}

// 	end_endpoits(cmd, fdi, fdo);
// 	return (0);
// }

int	check_in(t_redirections *node)
{
	int	fd;

	fd = -1;
	if (access(node->element[1], F_OK) == 0)
	{
		if (node->mode == FILE_OUT_TRUNC)
			fd = open(node->element[1], O_WRONLY | O_TRUNC);
		else if (node->mode == FILE_OUT_APPEND)
			fd = open(node->element[1], O_WRONLY | O_APPEND);
		else if (node->mode == FILE_IN_READ)
			fd = open(node->element[1], O_RDONLY);
	}
	else
	{
		printf("Minishell: %s: No such file or directory\n", node->element[1]);
		return (fd);
	}
	if (fd == -1)
	{
		printf("Minishell: %s: Permission denied \n", strerror(errno));
		return (fd);
	}
	return (fd);
}

int	check_out(t_redirections *node)
{
	int	fd;

	fd = -1;
	if (access(node->element[1], F_OK) == 0)
	{
		if (node->mode == FILE_OUT_TRUNC)
			fd = open(node->element[1], O_WRONLY | O_TRUNC);
		else if (node->mode == FILE_OUT_APPEND)
			fd = open(node->element[1], O_WRONLY | O_APPEND);
		else if (node->mode == FILE_IN_READ)
			fd = open(node->element[1], O_RDONLY);
	}
	else
	{
		printf("Minishell: %s: No such file or directory\n", node->element[1]);
		return (fd);
	}
	if (fd == -1)
	{
		printf("Minishell: %s: Permission denied \n", strerror(errno));
		return (fd);
	}
	return (fd);
}

/**
 * @ensures permissions for redirections from {@code node}
*/
int	permission_checker(t_redirections *node)
{
	int	fd;

	fd = -1;
	while (node)
	{
		if (fd != -1)
			close(fd);
		if (node->element[0] == ">")
			fd = check_out(node);
		else if (node->element[0] == "<")
			fd = check_in(node);
			
	}
	return (fd);
}
