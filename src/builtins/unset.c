/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:12:23 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/02 21:56:05 by pedromota        ###   ########.fr       */
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

static void	outfile(t_cmds *node)
{
	int	fd;

	fd = 1;
	if (node->next)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	if (dup2(fd, 1) == -1)
	{
		write(2, "Minishell: ", 12);
		perror("dup2");
		exit(1);
	}
	if (node->prev)
		close(node->prev->pipe[0]);
	if (node->pipe[0] != -1)
		close(node->pipe[0]);
	if (node->pipe[1] != -1)
		close(node->pipe[1]);
	if (node->redirection[0] != -1)
		close(node->redirection[0]);
	if (node->redirection[1] != -1)
		close(node->redirection[1]);
}

int	ft_unset(t_cmds *node)
{
	int i;

	i = 0;
	outfile(node);
	if (ft_strncmp(node->args[0], "unset", 6))
		return (0);
	if (!node->args[i])
		return (1);
	while (node->args[++i])
		remove_node(&node->sh->env, node->args[i]);
	return (1);
}