/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input_Output.utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 05:53:18 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 23:39:28 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

int	check_in(t_redirections *node)
{
	int	fd;
	int	acess;

	fd = -1;
	acess = access(node->element[1], F_OK | R_OK);
	if (acess == -1)
	{
		write(2, "Minishell: ", 11);
		write(2, node->element[1], ft_strlen(node->element[1]));
		write(2, " : ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
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

int	out_append(t_redirections *node)
{
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

static void	heredoc_setup(t_cmds *cmds, t_redirections *node, int *local)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		clean(cmds->sh, true, 1, "PIPE ERROR");
	cmds->redirection[0] = fd[0];
	ft_ml_sigdefault(SIG_STATE_IGNORE);
	pid = fork();
	if (pid == -1)
		clean(cmds->sh, true, 1, "FORK ERROR");
	if (!pid)
	{
		ft_ml_sigdefault(SIG_STATE_HD_CHILD);
		close(fd[0]);
		heredoc(cmds, node->element[1], fd[1]);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, local, 0);
		ft_ml_sigdefault(SIG_STATE_CHILD);
		*local = *local >> 8;
	}
}

int	permission_checker(t_redirections *node, t_cmds *cmds)
{
	int	fd;
	int	local;

	fd = -1;
	local = 0;
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
		heredoc_setup(cmds, node, &local);
		if (cmds->redirection[0] != -1)
			fd = cmds->redirection[0];
		if (cmds->redirection[0] == -2)
			clean(cmds->sh, true, 1, NULL);
		if (local == 130)
			clean(cmds->sh, true, 130, NULL);
	}
	return (fd);
}
