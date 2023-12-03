#include <minishell.h>

void	exec_ptr_chooser(t_cmds *node)
{
	if (!node->args || !node->args[0])
		node->ft_exec = &ft_exec;
	else if (!ft_strcmp(node->args[0], "echo"))
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
			clean(node->sh, true, 1, "Pipe Error");
}

void	setup_fd_for_next_fork(t_cmds *head)
{
	if (head->pipe[1] != -1)
		close(head->pipe[1]);
	if (head->prev && head->prev->pipe[0] != -1)
		close(head->prev->pipe[0]);
	if (!head->next && head->pipe[0] != -1)
		close(head->pipe[0]);
}

void	wait_for_child(t_shell *sh, int *processlist, int *process)
{
	int	status;

	while (*process > 0)
	{
		waitpid(processlist[--(*process)], &status, 0);
		sh->exit = status >> 8;
	}
	free(processlist);
}
