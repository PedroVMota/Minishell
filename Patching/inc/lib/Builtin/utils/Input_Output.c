/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input_Output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 23:32:46 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_in(t_redirections *node)
{
	int fd;
	int acess;

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

int check_out(t_redirections *node)
{
	int fd;
	int acess;

	fd = -1;
	acess = access(node->element[1], F_OK);
	if (!acess)
		fd = open(node->element[1], O_RDWR | O_TRUNC | 0644);
	else if (acess == -1)
		fd = open(node->element[1], O_RDWR | O_TRUNC | O_CREAT | 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->element[1], 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-2);
	}
	return (fd);
}

int out_append(t_redirections *node)
{
	int fd;
	int acess;

	fd = -1;
	acess = access(node->element[1], F_OK);
	if (!acess)
		fd = open(node->element[1], O_RDWR | O_APPEND | 0644);
	else if (acess == -1)
		fd = open(node->element[1], O_RDWR | O_APPEND | O_CREAT | 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->element[1], 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-2);
	}
	return (fd);
}

/**
 * @ensures permissions for redirections from {@code node}
 *  and creates files if neccessary
 */
// int	permission_checker_in(t_redirections *node, t_cmds *cmds)
// {
// 	int	fd;

// 	fd = -1;
// 	if (fd != -1)
// 		close(fd);
// 	if (!ft_strcmp(node->element[0], "\7"))
// 		fd = check_in(node);
// 	if (!ft_strcmp(node->element[0], "\7\7"))
// 	{
// 		heredoc(cmds, node->element[1]);
// 		if (cmds->redirection[0] != -1)
// 			fd = cmds->redirection[0];
// 	}
// 	return (fd);
// }

int permission_checker(t_redirections *node, t_cmds *cmds)
{
	int fd;

	fd = -1;
	if (fd != -1)
		close(fd);
	if (!ft_strcmp(node->element[0], "\6"))
		fd = check_out(node);
	else if (!ft_strcmp(node->element[0], "\6\6"))
		fd = out_append(node);
	else if (!ft_strcmp(node->element[0], "\7"))
		fd = check_in(node);
	else if (!ft_strcmp(node->element[0], "\7\7"))
	{
		heredoc(cmds, node->element[1]);
		if (cmds->redirection[0] != -1)
			fd = cmds->redirection[0];
		if (cmds->redirection[0] == -2)
			clean(cmds->sh, true, 1, NULL);
	}
	return (fd);
}

void redirect(t_cmds *node)
{
	t_redirections *in;
	t_redirections *out;

	in = node->infiles;
	out = node->outfile;
	while (in)
	{
		if (node->is_builtin == 1)
			node->saved_stdin = dup(0);
		if (node->redirection[0] > 0)
			close(node->redirection[0]);
		node->redirection[0] = permission_checker(in, node);
		if (node->redirection[0] == -2)
			node->shouldrun = 0;
		in = in->next;
	}
	while (out)
	{
		if (node->is_builtin == 1)
			node->saved_stdout = dup(1);
		if (node->redirection[1] > 0)
			close(node->redirection[1]);
		node->redirection[1] = permission_checker(out, node);
		if (node->redirection[1] == -2)
			node->shouldrun = 0;
		out = out->next;
	}
	if (node->redirection[1] == -2)
		clean(node->sh, true, 1, NULL);
}
