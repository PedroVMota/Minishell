/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPermission_utils0.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:53:51 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 21:30:22 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	add_directory(char **cmd);
int		shell_update_exit_status_error(int _new_err, t_shell *sh);
bool	f_perm(char *name, char **paths);

char	**getpaths(t_shell *sh)
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

void	set_relative_path(t_cmds *head, int *err)
{
	int		i;
	char	*tmp;
	char	**paths;

	if (isbuiltin(head) || !head->args)
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
	if (access(head->args[0], F_OK))
		return (shell_update_exit_status_error(127, head->sh));
	else if (access(head->args[0], X_OK) == -1)
		return (shell_update_exit_status_error(126, head->sh));
	return (shell_update_exit_status_error(0, head->sh));
}

int	check_all_paths(t_cmds *head, int *err, int *type)
{
	if ((head->args != NULL && head->args[0][0] != '\0') && \
	(ft_strnstr(head->args[0], "./", 2) || ft_strnstr(head->args[0], "../",
				3) || ft_strnstr(head->args[0], "/", 3)))
		*type = 2;
	if (!(head->args[0][0] == '\0') && *type == 1 && !isbuiltin(head))
		set_relative_path(head, err);
	else if (!(head->args[0][0] == '\0') && *type == 2)
		set_absolute_path(head);
	else if (head->args[0][0] == '\0')
	{
		*type = 1;
		head->sh->exit = 127;
	}
	return (0);
}
