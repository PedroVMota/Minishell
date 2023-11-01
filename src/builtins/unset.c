/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:12:23 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 21:38:43 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_env **head, char *content)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *head;
	while (current->next != NULL && ft_strcmp(current->vars[0], content))
	{
		previous = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (previous != NULL)
			previous->next = current->next;
		else
			*head = current->next;
		free(current);
	}
}

int	ft_unset(t_cmds *node)
{
	int	i;

	i = 0;
	if (ft_strncmp(node->args[0], "unset", 6))
		return (0);
	if (!node->args[i])
		return (1);
	while (node->args[++i])
		remove_node(&node->sh->env, node->args[i]);
	return (1);
}
