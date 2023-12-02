/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:47:46 by pedro             #+#    #+#             */
/*   Updated: 2023/11/29 14:29:26 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		f_perm(char *name, char **paths);

int	shell_update_exit_status_error(int _new_err, t_shell *sh)
{
	sh->exit = _new_err;
	return (sh->exit);
}

static void	add_directory(char **cmd)
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
	if (!list)
		return (NULL);
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

bool		isbuiltin(t_cmds *cmd);

void	set_relative_path(t_cmds *head, int *err)
{
	int		i;
	char	*tmp;
	char	**paths;

	if (isbuiltin(head))
		return ;
	paths = getpaths(head->sh);
	if (!paths)
		return ;
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], head->args[0]);
		if (!tmp)
			return ;
		if (f_perm(tmp, paths))
		{
			split_str_replace(head->args, 0, tmp);
			return ((void)(shell_update_exit_status_error(0, head->sh)));
		}
		free(tmp);
	}
	free_split(paths, 1);
	*err = 127;
}

int	set_absolute_path(t_cmds *head)
{
	if (access(head->args[0], X_OK) == -1)
		return (shell_update_exit_status_error(126, head->sh));
	else if (access(head->args[0], F_OK))
		return (shell_update_exit_status_error(127, head->sh));
	return (shell_update_exit_status_error(0, head->sh));
}
