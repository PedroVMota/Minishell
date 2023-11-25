/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:47:46 by pedro             #+#    #+#             */
/*   Updated: 2023/11/25 12:48:21 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shell_update_exit_status_error(int _new_err, t_shell *sh, char *msg)
{
	if(!sh)
		clean(sh, true, 1, msg);
	sh->exit = _new_err;
	return ;
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

bool	isbuiltin(t_cmds *cmd);

void	set_relative_path(t_cmds *head, int *err)
{
	int		i;
	char	*tmp;
	char	**paths;


	printf("%s%s%s\n", YEL, __func__, RESET);
	if(isbuiltin(head))
		return ;
	paths = getpaths(head->sh);
	if(!paths)
		return shell_update_exit_status_error(126, head->sh, "Cannot Execute Binary files");
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
	printf("%s%s%s\n", YEL, __func__, RESET);
	if (access(head->args[0], X_OK) == -1)
	{
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