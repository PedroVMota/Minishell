/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLinkList.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:41:05 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 21:15:41 by oharoon          ###   ########.fr       */
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
	node->infiles = NULL;
	node->outfile = NULL;
	node->ft_exec = NULL;
	node->args = ft_split(str, '\4');
	node->is_builtin = 0;
	node->saved_stdin = -1;
	node->saved_stdout = -1;
	node->shouldrun = 1;
	return (node);
}

t_cmds	*_add(char *cmd_line, t_cmds **head, t_shell *sh)
{
	t_cmds	*first;
	t_cmds	*last;
	t_cmds	*node;

	node = _create_node(cmd_line);
	if (!node)
		return (*head);
	node->sh = sh;
	last = ft_lstpos(*head);
	first = *head;
	if (!first)
		return (node);
	last->next = node;
	node->prev = last;
	return (first);
}
