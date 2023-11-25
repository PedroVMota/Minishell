/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/24 12:56:08 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool		isbuiltin(t_cmds *cmd);

void	exec_ptr_chooser(t_cmds *node)
{
	if (!node->args[0][0])
		node->ft_exec = NULL;
	if (!ft_strcmp(node->args[0], "echo"))
		node->ft_exec = &ft_echo;
	else if (!ft_strcmp(node->args[0], "cd"))
		node->ft_exec = &ft_cd;
	else if (!ft_strcmp(node->args[0], "pwd"))
		node->ft_exec = &ft_pwd;
	else if (!ft_strcmp(node->args[0], "export"))
		node->ft_exec = &ft_export;
	else if (!ft_strcmp(node->args[0], "unset"))
		node->ft_exec = &ft_unset;
	else if (!ft_strcmp(node->args[0], "env"))
		node->ft_exec = &ft_env;
	else if (!ft_strcmp(node->args[0], "exit"))
		node->ft_exec = &ft_exit;
	else
		node->ft_exec = &ft_exec;
}

void	pipeline(t_cmds *node)
{
	if (node->next)
		if (pipe(node->pipe) == -1)
			perror("pipe");
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

static void	run(t_cmds *head, int *processlist, int *process)
{
	bool	isfork;

	isfork = true;
	if (isbuiltin(head))
		isfork = false;
	if (!isfork)
		head->ft_exec(head);
	else if (isfork)
	{
		processlist[(*process)] = fork();
		if (processlist[(*process)] == 0)
		{
			free(processlist);
			if (head->ft_exec)
				head->ft_exec(head);
			clean(head->sh, true, 0, NULL);
		}
		(*process)++;
	}
}

int	software(t_shell *sh)
{
	int		*processlist;
	int		process;
	t_cmds	*head;

	process = 0;
	head = sh->cmds;
	processlist = ft_calloc(sh->lstsize, sizeof(int));
	if (!processlist)
		return (1);
	while (head)
	{
		pipeline(head);
		exec_ptr_chooser(head);
		permission_tester(head);
		run(head, processlist, &process);
		close_gen(head);
		head = head->next;
	}
	while (process > 0)
		waitpid(processlist[--process], NULL, 0);
	free(processlist);
	return (0);
}
