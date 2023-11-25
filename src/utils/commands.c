/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:17:05 by pedro             #+#    #+#             */
/*   Updated: 2023/11/25 12:59:42 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmds	*ft_lstpos(t_cmds *cmds)
{
	if (!cmds)
		return (NULL);
	while (cmds->next)
		cmds = cmds->next;
	return (cmds);
}

t_cmds	*_create_node(char *str)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (node == NULL)
		return (NULL);
	node->pipe[0] = -1;
	node->pipe[1] = -1;
	node->redirection[0] = -1;
	node->redirection[1] = -1;
	node->prev = NULL;
	node->next = NULL;
	node->args = ft_split(str, '\4');
	node->shouldrun = 1;
	return (node);
}

t_cmds	*_add(char *cmd_line, t_cmds **head, t_shell *sh)
{
	t_cmds	*first;
	t_cmds	*last;
	t_cmds	*node;

	node = _create_node(cmd_line);
	node->sh = sh;
	last = ft_lstpos(*head);
	first = *head;
	if (!first)
		return (node);
	last->next = node;
	node->prev = last;
	return (first);
}
