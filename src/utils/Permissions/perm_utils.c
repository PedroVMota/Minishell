/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:47:46 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:23:35 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	set_relative_path(t_cmds *head, int *err)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = getpaths(head->sh);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], head->args[0]);
		if (!tmp)
			return ;
		if (access(tmp, F_OK) == 0)
		{
			free(head->args[0]);
			free_split(paths, 1);
			head->args[0] = tmp;
			*err = 0;
			return ;
		}
		free(tmp);
	}
	free_split(paths, 1);
	*err = 127;
}

/*
	printf("ReadPermission: %d\n", access(head->args[0], R_OK));
	printf("WritePermission: %d\n", access(head->args[0], W_OK));
	printf("ExecutePermission: %d\n", access(head->args[0], X_OK));
	printf("FileExists: %d\n", access(head->args[0], F_OK));
*/
void	set_absolute_path(t_cmds *head, int *err)
{
	if (access(head->args[0], X_OK) == -1)
	{
		printf("\n%s Permission does not Exists\n", head->args[0]);
		*err = 126;
		return ;
	}
	else if (access(head->args[0], F_OK))
	{
		*err = 127;
		return ;
	}
	*err = 0;
}
