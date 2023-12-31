/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input_Output.utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 05:53:18 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 04:39:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

int	check_in(t_redirections *node){
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

int	check_out(t_redirections *node){
	int	fd;
	int	acess;

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

int	out_append(t_redirections *node){
	int	fd;
	int	acess;

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

int	permission_checker(t_redirections *node, t_cmds *cmds){
	int	fd;

	fd = -1;
	if (fd != -1)
		close(fd);
	if (node->mode == FILE_OUT_TRUNC)
		fd = check_out(node);
	else if (node->mode == FILE_OUT_APPEND)
		fd = out_append(node);
	else if (node->mode == FILE_IN_READ)
		fd = check_in(node);
	else if (node->mode == FILE_IN_HEREDOC)
	{
		heredoc(cmds, node->element[1]);
		if (cmds->redirection[0] != -1)
			fd = cmds->redirection[0];
		if (cmds->redirection[0] == -2)
			clean(cmds->sh, true, 1, NULL);
	}
	return (fd);
}
