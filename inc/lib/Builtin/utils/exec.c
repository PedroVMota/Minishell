/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:20:53 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

bool	checker(t_cmds *node)
{
	int	perm[2];

	permission_tester(node, perm);
	if (perm[0] == 127 && perm[1] == 2)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	else if (perm[0] == 127 && perm[1] == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		return (127);
	}
	else if (perm[0] == 126)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": Permission Denied\n", 2);
		return (126);
	}
	return (0);
}

void	close_all(t_cmds *l)
{
	if (l->pipe[0] != -1)
		close(l->pipe[0]);
	if (l->pipe[1] != -1)
		close(l->pipe[1]);
	if (l->redirection[0] != -1 && l->redirection[0] != -2)
		close(l->redirection[0]);
	if (l->redirection[1] != -1 && l->redirection[1] != -2)
		close(l->redirection[1]);
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

int	ft_exec(t_cmds *node)
{
	int	*dups;

	redirect(node);
	dups = set_dups(node);
	if (checker(node) == true)
	{
		free(dups);
		clean(node->sh, true, node->sh->exit, NULL);
	}
	clean_redirection(&node->infiles);
	clean_redirection(&node->outfile);
	free(dups);
	end_endpoits(node);
	if (!node->args || !node->args[0] || !node->args[0][0])
		clean(node->sh, true, 0, NULL);
	if (execve(node->args[0], node->args, node->sh->envp) != 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		clean(node->sh, true, errno, NULL);
	}
	return (0);
}
