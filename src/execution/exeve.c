#include <minishell.h>





//void	decider(t_cmds *node)
//{
//	if (!node || !node->args)
//		return ;
//	if (!ft_strcmp(node->args[0], "echo"))
//		node->ft_exec = &ft_echo;
//	else if (!ft_strcmp(node->args[0], "cd"))
//		node->ft_exec = &ft_cd;
//	else if (!ft_strcmp(node->args[0], "pwd"))
//		node->ft_exec = &ft_pwd;
//	else if (!ft_strcmp(node->args[0], "export"))
//		node->ft_exec = &ft_export;
//	else if (!ft_strcmp(node->args[0], "unset"))
//		node->ft_exec = &ft_unset;
//	else if (!ft_strcmp(node->args[0], "env"))
//		node->ft_exec = &ft_env;
//	else if (!ft_strcmp(node->args[0], "exit"))
//		node->ft_exec = &ft_exit;
//	else
//		node->ft_exec = &ft_exec;
//}



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

int	software(t_cmds *head)
{
	int	*processlist;

	processlist = ft_calloc(g_shell.lstsize, sizeof(int));
	if (!processlist)
		return (1);
	while (head)
	{
		if (isbuiltin(head) || permission_tester(head))
		{
			head = head->next;
			continue ;
		}
		head = head->next;
	}
	free(processlist);
	return (0);
}
