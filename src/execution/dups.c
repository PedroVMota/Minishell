/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/24 19:19:33 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	standard_choiser(t_cmds *cmd)
{
	int	fdi;
	int	fdo;

	fdi = -1;
	fdo = -1;
	// all in
	if (cmd->prev)
		fdi = cmd->prev->pipe[0];
	if (cmd->redirection[0] != -1)
		fdi = cmd->redirection[0];
	// all out
	if (cmd->pipe[1] != -1)
		fdo = cmd->pipe[1];
	if (cmd->redirection[1] != -1)
		fdo = cmd->redirection[1];
	// case -1 default values
	if (fdi == -1)
		fdi = STDIN_FILENO;
	if (fdo == -1)
		fdo = STDOUT_FILENO;
	printf("fdi: %s%d%s\n", YEL, fdi, RESET);
	printf("fdo: %s%d%s\n", YEL, fdo, RESET);
	// dup2
	if (dup2(fdi, STDIN_FILENO) == -1)
		perror("dup2 1" );
	if (dup2(fdo, STDOUT_FILENO) == -1)
		perror("dup2 2");
	// close
	if(cmd->prev)
		close(cmd->prev->pipe[0]);
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
	if (cmd->redirection[0] != -1)
		close(cmd->redirection[0]);
	if (cmd->redirection[1] != -1)
		close(cmd->redirection[1]);
	return (0);
}
