/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:02:15 by pedro             #+#    #+#             */
/*   Updated: 2023/11/25 13:21:38 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_relative_path(t_cmds *head, int *err);
void set_absolute_path(t_cmds *head, int *err);

int check_all_paths(t_cmds *head, int *err, int *type)
{
	*type = 1; // relative
	if (ft_strnstr(head->args[0], "./", 2) || ft_strnstr(head->args[0], "../", 3))
		*type = 2; // absolute
	if (!isbuiltin(head) && *type == 1)
	{
		printf("%s%s%s\n", YEL, __func__, RESET);
		set_relative_path(head, err);
	}
	else if (*type == 2)
	{
		printf("%s%s%s", RED, __func__, RESET);
		set_absolute_path(head, err);
	}

	if (*err != 0)
	{
		write(2, "Error: Minishell: ", 19);
		write(2, head->args[0], ft_strlen(head->args[0]));
	}
	return (0);
}

bool permission_tester(t_cmds *head)
{
	int type;

	check_all_paths(head, &head->sh->exit, &type);
	if (head->sh->exit == 127 && type == 1)
	{
		write(2, ": command not found\n", 20);
		return (false);
	}
	else if (head->sh->exit == 126 && type == 1)
	{
		write(2, ": Cannot execute binary files\n", 31);
		return (false);
	}
	else if (head->sh->exit == 127 && type == 2)
	{
		write(2, ": No such file or directory\n", 28);
		return (false);
	}
	else if (head->sh->exit == 126)
	{
		write(2, ": Permission denied\n", 20);
		return (false);
	}
	return (true);
}
