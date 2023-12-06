/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:51:41 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		wait_for_child(t_shell *sh, int *processlist, int *process);
void		run_parrent(t_cmds *node, int *ps);

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

int	command_exe(t_cmds *cmd, int *ps, int *p)
{
	int	isfork;

	isfork = true;
	if (isbuiltin(cmd) && !(cmd->prev || cmd->next))
	{
		cmd->is_builtin = 1;
		isfork = false;
	}
	if (!isfork)
		run_parrent(cmd, ps);
	else if ((isfork))
	{
		ps[*p] = fork();
		if (ps[*p] == 0)
		{
			free(ps);
			if (cmd->ft_exec)
				cmd->ft_exec(cmd);
			clean(cmd->sh, true, 0, NULL);
		}
	}
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
		command_exe(head, processlist, &process);
		close_gen(head);
		process++;
		head = head->next;
	}
	wait_for_child(sh, processlist, &process);
	return (0);
}
