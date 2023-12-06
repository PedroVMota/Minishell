/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:46:23 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:47:55 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_split(char **split, int ret)
{
	char	**ptr;

	ptr = split;
	if (!ptr)
		return (0);
	while (*ptr)
	{
		if (*ptr)
			free(*ptr);
		ptr++;
	}
	free(split);
	return (ret);
}

void	clean_redirection(t_redirections **head)
{
	t_redirections	*local;
	t_redirections	*next;

	local = *head;
	while (local)
	{
		free_split(local->element, 0);
		next = local->next;
		free(local);
		local = next;
	}
}

int	ft_env_delete(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		if ((*env)->vars)
			free_split((*env)->vars, 1);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}
