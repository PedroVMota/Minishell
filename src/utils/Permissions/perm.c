/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:02:15 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:32:40 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_relative_path(t_cmds *head, int *err);
void		set_absolute_path(t_cmds *head, int *err);

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

int	check_all_paths(t_cmds *head, int *err, int *type)
{
	*type = 1;
	if (ft_strnstr(head->args[0], "./", 2) || ft_strnstr(head->args[0], "../",
			3))
		*type = 2;
	if (*type == 1)
		set_relative_path(head, err);
	else if (*type == 2 || !isbuiltin(head))
		set_absolute_path(head, err);
	if (*err != 0)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, head->args[0], ft_strlen(head->args[0]));
	}
	return (0);
}

bool	permission_tester(t_cmds *head)
{
	int	type;

	check_all_paths(head, &head->sh->exit, &type);
	if (head->sh->exit == 127 && type == 1)
	{
		write(2, ": command not found\n", 20);
		return (true);
	}
	else if (head->sh->exit == 127 && type == 2)
	{
		write(2, ": No such file or directory\n", 28);
		return (true);
	}
	else if (head->sh->exit == 126)
	{
		write(2, ": Permission denied\n", 20);
		return (true);
	}
	return (false);
}
