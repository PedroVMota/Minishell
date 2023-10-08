/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:02:48 by pedro             #+#    #+#             */
/*   Updated: 2023/09/21 18:03:43 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_split(char **split)
{
	char **ptr;

	ptr = split;
	if (!split)
		return;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
}

void clean_commands(t_cmds **cmds)
{
	t_cmds *ptr;
	t_cmds *next;

	next = NULL;
	ptr = *cmds;
	if (!ptr)
		return;
	while (ptr)
	{
		if (ptr->args)
			free_split(ptr->args);
		if (ptr->pipe[0] != -1 && ptr->pipe[0] != 0 && ptr->pipe[0] != 1 && ptr->pipe[0] != 2)
			close(ptr->pipe[0]);
		if (ptr->pipe[1] != -1 && ptr->pipe[1] != 0 && ptr->pipe[1] != 1 && ptr->pipe[1] != 2)
			close(ptr->pipe[1]);
		if (ptr->redirection[0] != -1 && ptr->redirection[0] != 0 && ptr->redirection[0] != 1 && ptr->redirection[0] != 2)
			close(ptr->redirection[0]);
		if (ptr->redirection[1] != -1 && ptr->redirection[1] != 0 && ptr->redirection[1] != 1 && ptr->redirection[1] != 2)
			close(ptr->redirection[1]);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}

int ft_env_delete(t_env **env)
{
	t_env *tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free_split((*env)->vars);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}
