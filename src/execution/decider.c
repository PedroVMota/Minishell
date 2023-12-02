#include <minishell.h>

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
		cmd->ft_exec(cmd);
	else if ((isfork))
	{
		ps[*p] = fork();
		if (ps[*p] == 0)
		{
			free(ps);
			if (cmd->ft_exec)
				cmd->ft_exec(cmd);
			clean(cmd->sh, true, 1, NULL);
		}
	}
	(*p)++;
	return (0);
}

static void	precedure_for_execution(t_cmds *head, int *ps, int *p)
{
	pipeline(head);
	permission_tester(head);
	exec_ptr_chooser(head);
	command_exe(head, ps, p);
	setup_fd_for_next_fork(head);
}

int	execution_part(t_shell *sh)
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
		precedure_for_execution(head, processlist, &process);
		head = head->next;
	}
	wait_for_child(sh, processlist, &process);
	return (0);
}
