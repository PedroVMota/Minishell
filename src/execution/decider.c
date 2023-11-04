/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/04 14:08:29 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_ptr_chooser(t_cmds *node)
{
	if (!node->args[0][0])
		return ;
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

static void	execute_command(t_cmds *head, int *pl, int *pid)
{
	bool		forked;
	pid_t		pid_val;
	const char	*notforked[7] = {"echo", "cd", "pwd", "export", "unset"};
	forked = true;
	pid_val = -1;
	for (int index = 0; index < 5 && forked == true; index++)
		if (!ft_strcmp(head->args[0], notforked[index]))
			forked = false;
	
	if (forked)
		pid_val = fork();
	if (pid_val == 0)
	{
		head->ft_exec(head);
		exit(0);
	}
	else if (pid_val == -1)
		head->ft_exec(head);
	pl[(*pid)++] = pid_val;
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
		execute_command(head, processlist, &process);
		close_gen(head);
		head = head->next;
	}
	while (process > 0)
		waitpid(processlist[--process], NULL, 0);
	free(processlist);
	return (0);
}
