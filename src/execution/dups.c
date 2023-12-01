/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/01 22:19:46 by oharoon          ###   ########.fr       */
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
	int	acess;

	fd = -1;
	acess = access(node->element[1], F_OK | R_OK);
	if (acess == -1)
	{
		printf("Minishell: %s:\n", strerror(errno));
		return (-2);
	}
	fd = open(node->element[1], O_RDONLY);
	return (fd);
}

int	check_out(t_redirections *node)
{
	int	fd;
	int	acess;

	fd = -1;
	acess = access(node->element[1], F_OK);
	if(!acess)
		fd = open(node->element[1], O_RDWR | O_TRUNC | 0644);
	else if (acess == -1)
		fd = open(node->element[1], O_RDWR | O_TRUNC | O_CREAT | 0644);
	if (fd == -1)
		printf("Minishell: %s\n", strerror(errno));
	return (fd);
}

int	out_append(t_redirections *node)
{
	int	fd;
	int	acess;

	fd = -1;
	acess = access(node->element[1], F_OK);
	if(!acess)
		fd = open(node->element[1], O_RDWR | O_APPEND | 0644);
	else if (acess == -1)
		fd = open(node->element[1], O_RDWR | O_APPEND | O_CREAT | 0644);
	if (fd == -1)
		printf("Minishell: %s\n", strerror(errno));
	return (fd);
}

/**
 * @ensures permissions for redirections from {@code node} and creates files if neccessary
*/
int	permission_checker_in(t_redirections *node, t_cmds *cmds)
{
	int	fd;

	fd = -1;
	if (fd != -1)
		close(fd);
	if (!ft_strcmp(node->element[0], "\7"))
		fd = check_in(node);
	printf("\n%s\n", node->element[0]);
	if (!ft_strcmp(node->element[0], "\b"))
	{
		printf("\n2\n");
		printf("\n%s\n", node->element[1]);
		heredoc(cmds, node->element[1]);
		if(cmds->redirection[0] != -1)
			fd = cmds->redirection[0];
	}
	printf("\n3s\n");
	return (fd);
}

int permission_checker_out(t_redirections *node)
{
	int	fd;

	fd = -1;
	if (fd != -1)
		close(fd);
	if (!ft_strcmp(node->element[0], "\6"))
		fd = check_out(node);
	else if (!ft_strcmp(node->element[0], "\6\6"))
		fd = out_append(node);

	return (fd);
}

void redirect(t_cmds *node)
{
    while (node->infiles)
	{
		if (node->redirection[0] > 0)
			close(node->redirection[0]);
		printf("----------------------------------------\n");
		for (int i = 0; i < 2; i++)
		{
			printf("%s", node->infiles->element[0]);
			printf("%s", node->infiles->element[1]);
			node->infiles = node->infiles->next;
		}
		printf("----------------------------------------\n");
		
		node->redirection[0] = permission_checker_in(node->infiles, node);
		node->infiles = node->infiles->next;
	}
	dup2(node->redirection[0], 0);
	while (node->outfile)
	{
		if (node->redirection[1] > 0)
			close(node->redirection[1]);
		node->redirection[1] = permission_checker_out(node->outfile);
		node->outfile = node->outfile->next;
	}
	dup2(node->redirection[1], 1);
}

void close_redi(t_cmds *node)
{
	if (node->redirection[0] != -1 && node->redirection[0] != 2)
		close(node->redirection[0]);
	if (node->redirection[1] != -1 && node->redirection[1] != 2)
		close(node->redirection[1]);
}