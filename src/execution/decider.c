/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 16:08:40 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exec_ptr_chooser(t_cmds *node)
{
	if (!node || !node->args)
		return;
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

void pipeline(t_cmds *node)
{
	if (node->next)
		if (pipe(node->pipe) == -1)
			perror("pipe");
}

void close_gen(t_cmds *head)
{
	if (head->pipe[1] != -1)
		close(head->pipe[1]);
	if (head->prev && head->prev->pipe[0] != -1)
		close(head->prev->pipe[0]);
	if (!head->next && head->pipe[0] != -1)
		close(head->pipe[0]);
}

int command_exe(t_cmds *cmd, int *ps, int *p)
{
	int isfork = true;

	if (isbuiltin(cmd) && !(cmd->prev || cmd->next))
		isfork = false;
	if (!isfork)
	{
		printf("%s================= PARENT PROCESS %d =================%s\n", MAG, getpid(), RESET);
		printf("%sExecuting Command%s: {%s}\n", MAG, RESET, cmd->args[0]);
		printf("%s================= PARENT PROCESS %d =================%s\n", MAG, getpid(), RESET);
		cmd->ft_exec(cmd);
	}
	else if ((isfork))
	{
		ps[*p] = fork();
		if (ps[*p] == 0)
		{
			free(ps);
			printf("%s================= CHILD PROCESS %d =================%s\n", MAG, getpid(), RESET);
			printf("%sExecuting Command%s: {%s}\n", MAG, RESET, cmd->args[0]);
			printf("%s================= CHILD PROCESS %d =================%s\n", MAG, getpid(), RESET);
			cmd->ft_exec(cmd);
			exit(0);
		}
	}
	return 0;
}

int software(t_shell *sh)
{
	int *processlist;
	int process;
	t_cmds *head;

	process = 0;
	head = sh->cmds;
	processlist = ft_calloc(sh->lstsize, sizeof(int));
	if (!processlist)
		return (1);
	while (head)
	{
		pipeline(head); // check if there is a next if yes pipe.
		permission_tester(head);
		exec_ptr_chooser(head);
		command_exe(head, processlist, &process);
		close_gen(head);
		process++;
		head = head->next;
	}
	while (process > 0)
		waitpid(processlist[--process], NULL, 0);
	free(processlist);
	return (0);
}
