#include <minishell.h>

int	ft_echo(t_cmds *node)
{
	(void)node;
	return (0);
}
int	ft_cd(t_cmds *node)
{
	(void)node;
	return (0);
}
int	ft_pwd(t_cmds *node)
{
	(void)node;
	return (0);
}
int	ft_export(t_cmds *node)
{
	(void)node;
	return (0);
}
int	ft_unset(t_cmds *node)
{
	(void)node;
	return (0);
}

int	ft_exit(t_cmds *node)
{
	(void)node;
	return (0);
}
int	ft_exec(t_cmds *node)
{
	standard_choiser(node);
	if (execve(node->args[0], node->args, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
	return (0);
}

void	decider(t_cmds *node)
{
	if (!node || !node->args)
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

bool	isbuiltin(t_cmds *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (true);
	return (false);
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
		decider(head);
		if (isbuiltin(head) || permission_tester(head))
		{
			processlist[process] = fork();
			if (processlist[process] == 0)
				head->ft_exec(head);
			head = head->next;
			continue ;
		}
		processlist[process] = fork();
		if (processlist[process] == 0)
			head->ft_exec(head);
		head = head->next;
	}
	while (process-- > 0)
	{
		printf("Waiting for process %d\n", processlist[process]);
		waitpid(processlist[process], NULL, 0);
	}
	free(processlist);
	return (0);
}
