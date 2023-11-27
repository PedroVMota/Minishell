/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:02:15 by pedro             #+#    #+#             */
/*   Updated: 2023/11/27 03:45:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_relative_path(t_cmds *head, int *err);
void set_absolute_path(t_cmds *head, int *err);

int check_all_paths(t_cmds *head, int *err, int *type)
{
	*type = 1;
	if (ft_strnstr(head->args[0], "./", 2) || ft_strnstr(head->args[0], "../", 3))
		*type = 2;
	if (!isbuiltin(head) && *type == 1)
		set_relative_path(head, err);
	else if (*type == 2)
		set_absolute_path(head, err);
	return (0);
}

bool permission_tester(t_cmds *head)
{
	int type;

	check_all_paths(head, &head->sh->exit, &type);
	if (head->sh->exit == 127 && type == 1)
		return (false);
	else if (head->sh->exit == 127 && type == 2)
		return (false);
	else if (head->sh->exit == 126)
		return (false);
	return (true);
}
