/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionLinkList.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:37:49 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:40:59 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirections	*all_together(int *i, t_cmds *cm, t_type type);
t_type			red_type_checker(char *str);
void			redirection_in(t_type redi_node, t_cmds *node, int *i,
					t_shell *sh);
void			redirection_out(t_type redi_node, t_cmds *node, int *i,
					t_shell *sh);

t_redirections	*redirection_last_ptr(t_redirections *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	placer(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	if (redi_node == FILE_IN_HEREDOC || redi_node == FILE_IN_READ)
		redirection_in(redi_node, node, i, sh);
	if (redi_node == FILE_OUT_TRUNC || redi_node == FILE_OUT_APPEND)
		redirection_out(redi_node, node, i, sh);
}

void	redirection(t_cmds *node, t_shell *sh)
{
	char	**args;
	t_type	red_mode;
	int		i;
	int		loop;

	red_mode = FILE_NONE;
	i = 0;
	args = node->args;
	loop = -1;
	while (args[i])
	{
		remove_quotes(args[i]);
		red_mode = red_type_checker(args[i]);
		placer(red_mode, node, &i, sh);
		if (red_mode == FILE_NONE)
			i++;
		loop++;
	}
	if (!node->args[0])
	{
		free(node->args);
		node->args = NULL;
	}
}
