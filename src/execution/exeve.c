#include <minishell.h>

void add_directory(char **cmd)
{
	int i = -1;
	char *old_cmd;

	while (cmd[++i])
	{
		old_cmd = cmd[i];
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			continue;
		cmd[i] = ft_strjoin(cmd[i], "/");
		if (!cmd[i])
			return;
		free(old_cmd);
	}
}

static char **getpaths(void)
{
	t_env *list = g_shell.env;

	char **paths;

	paths = NULL;
	while (list)
	{
		if (!ft_strcmp("PATH", list->vars[0]))
		{
			paths = ft_split(list->vars[1], ':');
			add_directory(paths);
			return paths;
		}
		list = list->next;
	}
	free_split(paths);
	list = NULL;
	return NULL;
}

int find_command(t_cmds *cmd)
{
	char **paths;
	int index;
	char *new_command;

	index = -1;
	paths = getpaths();
	if (!paths)
		return 1;
	if (!access(cmd->args[0], F_OK))
		return 0;
	while (paths[++index])
	{
		new_command = ft_strjoin(paths[index], cmd->args[0]);
		if (!new_command)
		{
			free_split(paths);
			return 1;
		}
		if (!access(new_command, F_OK))
		{
			free(cmd->args[0]);
			cmd->args[0] = new_command;
			free_split(paths);
			return 0;
		}
		free(new_command);
	}
	free_split(paths);
	return 2;
}

bool isbuiltin(t_cmds *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return true;
	if (!ft_strcmp(cmd->args[0], "cd"))
		return true;
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return true;
	if (!ft_strcmp(cmd->args[0], "export"))
		return true;
	if (!ft_strcmp(cmd->args[0], "unset"))
		return true;
	if (!ft_strcmp(cmd->args[0], "env"))
		return true;
	if (!ft_strcmp(cmd->args[0], "exit"))
		return true;
	return false;
}

int software(t_cmds *head)
{
	int *processlist;

	processlist = ft_calloc(g_shell.lstsize, sizeof(int));
	if (!processlist)
		return 1;
	while (head)
	{
		if(isbuiltin(head))
		{
			head = head->next;
			continue;
		}
		if (find_command(head))
		{
			write(2, "Minishell: ", 12);
			write(2, head->args[0], ft_strlen(head->args[0]));
			write(2, " : Command not found\n", 22);
			g_shell.exit = 127;
			head = head->next;
			break;
		}
		if (-1 == access(head->args[0], X_OK))
		{
			write(2, "Minishell: ", 12);
			write(2, head->args[0], ft_strlen(head->args[0]));
			write(2, " : Permission denied\n", 22);
			g_shell.exit = 126;
			head = head->next;
			break;
		}
		head = head->next;
	}
	free(processlist);
	return 0;
}
