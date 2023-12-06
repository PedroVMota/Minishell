/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:12:23 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 22:59:11 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_node(t_env **head, char *content)
{
	t_env *current;
	t_env *previous;

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
		free_split(current->vars, 0);
		free(current);
	}
}

int ft_unset(t_cmds *node)
{
	int i;
	int *dups;

	i = 0;
	redirect(node);
	dups = set_dups(node);
	if (!dups)
		NULL;
	if (!node->args[i])
	{
		close_redi(node);
		return (1);
	}
	while (node->args[++i])
		remove_node(&node->sh->env, node->args[i]);
	close_redi(node);
	if(dups[0] != -10)
		close(dups[0]);
	if(dups[1] != -10)
		close(dups[1]);
	free(dups);
	return (1);
}
