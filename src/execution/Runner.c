/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:14:05 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		child_process_signal_updater(t_cmds *cmd);
void		execute_command(t_cmds *cmd, int *isfork, int **ps, int *p);

static int	get_command_size(t_cmds *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		if (head->is_builtin && !(head->prev || head->next))
			i -= 1;
		head = head->next;
	}
	return (i);
}

void	pipeline(t_cmds *node)
{
	if (node->next)
		if (pipe(node->pipe) == -1)
			clean(node->sh, true, 1, "Pipe Setup Error\n");
}

void	close_gen(t_cmds *head)
{
	if (head->pipe[1] != -1)
		close(head->pipe[1]);
	if (head->prev && head->prev->pipe[0] != -1)
		close(head->prev->pipe[0]);
	if (!head->next && head->pipe[0] != -1)
		close(head->pipe[0]);
}

int	command_exe(t_cmds *cmd, int **ps, int *p)
{
	int	isfork;

	isfork = true;
	if (cmd->sh->stop == 1)
		return (0);
	if (isbuiltin(cmd) && !(cmd->prev || cmd->next))
	{
		cmd->is_builtin = 1;
		isfork = false;
	}
	execute_command(cmd, &isfork, ps, p);
	return (0);
}

int	execution_part(t_shell *sh)
{
	int		*processlist;
	int		process;
	t_cmds	*head;

	process = 0;
	head = sh->cmds;
	processlist = ft_calloc(get_command_size(head), sizeof(int));
	if (!processlist)
		return (1);
	while (head)
	{
		pipeline(head);
		exec_ptr_chooser(head);
		command_exe(head, &processlist, &process);
		close_gen(head);
		process++;
		head = head->next;
	}
	wait_for_child(sh, &processlist, &process);
	return (0);
}
