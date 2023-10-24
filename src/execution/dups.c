/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/24 20:37:02 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_in(t_cmds *node)
{
	int	fd;

	fd = 0;
	if (!node)
		return (-1);
	if (node->prev)
		fd = node->prev->pipe[0];
	if (node->redirection[0] != -1)
		fd = node->redirection[0];
	return (fd);
}
static int	get_ou(t_cmds *node)
{
	int	fd;

	fd = 1;
	if (!node)
		return (-1);
	if (node->prev)
		fd = node->prev->pipe[0];
	if (node->redirection[0] != -1)
		fd = node->redirection[0];
	return (fd);
}

static void	end_endpoits(t_cmds *cmd)
{
	if (cmd->prev)
		close(cmd->prev->pipe[0]);
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
	if (cmd->redirection[0] != -1)
		close(cmd->redirection[0]);
	if (cmd->redirection[1] != -1)
		close(cmd->redirection[1]);
}

int	standard_choiser(t_cmds *cmd)
{
	int	fdi;
	int	fdo;

	fdi = get_in(cmd);
	fdo = get_ou(cmd);
	printf("fdi: %s%d%s\n", YEL, fdi, RESET);
	printf("fdo: %s%d%s\n", YEL, fdo, RESET);
	if (dup2(fdi, STDIN_FILENO) == -1)
	{
		write(2, "Minishell: ", 11);
		perror("dup2");
	}
	if (dup2(fdo, STDOUT_FILENO) == -1)
	{
		write(2, "Minishell: ", 11);
		perror("dup");
	}
	end_endpoits(cmd);
	return (0);
}
