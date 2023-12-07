/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:45:49 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/07 21:36:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_fds(t_cmds *cmds)
{
	if (cmds->pipe[0] != -1)
		close(cmds->pipe[0]);
	if (cmds->pipe[1] != -1)
		close(cmds->pipe[1]);
	if (cmds->redirection[0] != -1 && cmds->redirection[0] != -2)
		close(cmds->redirection[0]);
	if (cmds->redirection[1] != -1 && cmds->redirection[1] != -2)
		close(cmds->redirection[1]);
}

void	close_redi(t_cmds *node)
{
	if (node->redirection[0] != -1 && node->redirection[0] != 2)
		close(node->redirection[0]);
	if (node->redirection[1] != -1 && node->redirection[1] != 2)
		close(node->redirection[1]);
	if (node->is_builtin == 1)
	{
		if (node->saved_stdin != -1)
		{
			dup2(node->saved_stdin, 0);
			close(node->saved_stdin);
			node->saved_stdin = -1;
		}
		if (node->saved_stdout != -1)
		{
			dup2(node->saved_stdout, 1);
			close(node->saved_stdout);
			node->saved_stdout = -1;
		}
	}
}

void	clean_commands(t_cmds **cmds)
{
	t_cmds	*tmp;

	tmp = NULL;
	if (!(*cmds))
		return ;
	while (*cmds)
	{
		close_fds(*cmds);
		if ((*cmds)->args)
			free_split((*cmds)->args, 1);
		if ((*cmds)->infiles)
			clean_redirection(&(*cmds)->infiles);
		if ((*cmds)->outfile)
			clean_redirection(&(*cmds)->outfile);
		tmp = (*cmds)->next;
		free(*cmds);
		*cmds = tmp;
	}
	*cmds = NULL;
}

int	clean(t_shell *sh, bool _exit, int status, char *msg)
{
	if (!sh)
		return (1);
	clean_commands(&sh->cmds);
	if (_exit)
	{
		if (msg)
			write(2, msg, ft_strlen(msg));
		ft_env_delete(&sh->env);
		close(1);
		close(0);
		exit(status);
	}
	return (0);
}
