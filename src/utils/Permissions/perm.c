#include "minishell.h"

void	add_directory(char **cmd)
{
	int		i;
	char	*old_cmd;

	i = -1;
	while (cmd[++i])
	{
		old_cmd = cmd[i];
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			continue ;
		cmd[i] = ft_strjoin(cmd[i], "/");
		if (!cmd[i])
			return ;
		free(old_cmd);
	}
}

static char	**getpaths(t_shell *sh)
{
	t_env	*list;
	char	**paths;

	list = sh->env;
	paths = NULL;
	while (list)
	{
		if (!ft_strcmp("PATH", list->vars[0]))
		{
			paths = ft_split(list->vars[1], ':');
			add_directory(paths);
			return (paths);
		}
		list = list->next;
	}
	free_split(paths);
	list = NULL;
	return (NULL);
}

int	find_command(t_cmds *cmd)
{
	char	**paths;
	int		index;
	char	*new_command;

	index = -1;
	paths = getpaths(cmd->sh);
	if (!access(cmd->args[0], F_OK))
		return (0);
	while (paths[++index] && paths)
	{
		new_command = ft_strjoin(paths[index], cmd->args[0]);
		if (!new_command)
		{
			free_split(paths);
			return (1);
		}
		if (!access(new_command, F_OK))
		{
			split_str_replace(&cmd->args[0], 0, new_command);
			free_split(paths);
			return (0);
		}
		free(new_command);
	}
	free_split(paths);
	return (2);
}

bool	permission_tester(t_cmds *head)
{
	if (find_command(head))
	{
		write(2, "Minishell: ", 12);
		write(2, head->args[0], ft_strlen(head->args[0]));
		write(2, " : Command not found\n", 22);
		head->sh->exit = 127;
		return true;
	}
	if (-1 == access(head->args[0], X_OK))
	{
		write(2, "Minishell: ", 12);
		write(2, head->args[0], ft_strlen(head->args[0]));
		write(2, " : Permission denied\n", 22);
		head->sh->exit = 126;
		return true;
	}
	return false;
}