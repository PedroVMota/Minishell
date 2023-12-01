/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/28 01:03:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_in(t_cmds *node)
{
	int	fd;

	fd = -1;
	if (node->prev && node->prev->pipe[0] != -1)
		fd = node->prev->pipe[0];
	if (node->redirection[0] != -1)
		fd = node->redirection[0];
	return (fd);
}

int	get_ou(t_cmds *node)
{
	int	fd;

	fd = -1;
	if (node->next && node->pipe[1] != -1)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	return (fd);
}

static void	end_endpoits(t_cmds *cmd, int fdi, int fdo)
{
	if (cmd->prev)
	{
		close(cmd->prev->pipe[0]);
	}
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
	if (cmd->redirection[0] != -1)
		close(cmd->redirection[0]);
	if (cmd->redirection[1] != -1)
		close(cmd->redirection[1]);
	if (fdi != -1)
		close(fdi);
	if (fdo != -1)
		close(fdo);
}

int	standard_choiser(t_cmds *cmd)
{
	int	fdi;
	int	fdo;

	fdi = -1;
	fdo = -1;
	if (fdi != -1)
	{
		dup2(fdi, STDIN_FILENO);
		close(fdi);
	}
	if (fdo != -1)
	{
		dup2(fdo, STDOUT_FILENO);
		close(fdi);
	}
	end_endpoits(cmd, fdi, fdo);
	return (0);
}
