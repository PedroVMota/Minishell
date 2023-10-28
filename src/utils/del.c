/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:02:48 by pedro             #+#    #+#             */
/*   Updated: 2023/10/24 19:06:19 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_split(char **split, int ret)
{
	char	**ptr;

	ptr = split;
	if (!split)
		return (1);
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
	return (ret);
}

void	clean_commands(t_cmds **cmds)
{
	t_cmds	*ptr;
	t_cmds	*next;

	next = NULL;
	ptr = *cmds;
	if (!ptr)
		return ;
	while (ptr)
	{
		if (ptr->args)
			free_split(ptr->args, 1);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}

int	ft_env_delete(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free_split((*env)->vars, 1);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}
