/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/23 22:44:55 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	standard_choiser(t_cmds *cmd)
{
	if (cmd->pipe[0] != -1)
	{
		printf("pipe[0] = %d\n", cmd->pipe[0]);
		if (dup2(cmd->pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	if (cmd->redirection[0] != -1)
	{
		printf("redirection[0] = %d\n", cmd->redirection[0]);
		if (dup2(cmd->redirection[0], STDIN_FILENO) == -1)
			perror("dup2");
		if (cmd->redirection[0] != 1 && cmd->redirection[0] != 2
			&& cmd->redirection[0] != 0)
			close(cmd->redirection[0]);
	}
	if (cmd->pipe[1] != -1)
	{
		if (dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (cmd->pipe[1] != 1 && cmd->pipe[1] != 2 && cmd->pipe[1] != 0)
			close(cmd->pipe[1]);
	}
	if (cmd->redirection[1] != -1)
	{
		if (dup2(cmd->redirection[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (cmd->redirection[1] != 1 && cmd->redirection[1] != 2
			&& cmd->redirection[1] != 0)
			close(cmd->redirection[1]);
	}
	return 0;
}
