#include "minishell.h"

static bool	isbuiltin(t_cmds *cmd)
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

char	**getpaths(t_shell *sh)
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
	free_split(paths, 1);
	list = NULL;
	return (NULL);
}

int	check_all_paths(char **paths, t_cmds *head, int *err)
{ 
	int		i;
	char	*cmd_path;

	i = -1;
	cmd_path = NULL;
	if (!head->args[0][0])
	{
		*err = 127;
		return (0);
	}
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], head->args[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
			{
				split_str_replace(&head->args[0], 0, cmd_path);
				*err = 0;
				return (0);
			}
			else
			{
				*err = 126;
				free(cmd_path);
				return (0);
			}
		}
		else
			*err = 127;
		free(cmd_path);
	}
	return (0);
}

bool	permission_tester(t_cmds *head)
{
	char	**paths;

	if (isbuiltin(head))
		return (false);
	paths = getpaths(head->sh);
	if (!paths)
		return (false);
	check_all_paths(paths, head, &head->sh->exit);
	if (head->sh->exit == 126 || head->sh->exit == 127)
	{
		write(2, "Minishell: ", 12);
		perror(head->args[0]);
		free_split(paths, 1);
		return (true);
	}
	free_split(paths, 1);
	return (false);
}
