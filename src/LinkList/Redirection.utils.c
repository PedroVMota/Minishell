/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirection.utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:38:30 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:43:57 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redi_checker(char ***new, t_shell *sh)
{
	int	i;

	i = -1;
	while ((*new)[0][++i])
	{
		if ((*new)[0][i] == '\7' || (*new)[0][i] == '\6'
			|| (*new)[0][i] == '\b')
			continue ;
		else
			break ;
	}
	(*new)[1] = ft_strdup(&(*new)[0][i]);
	if (!(*new)[1])
		clean(sh, true, 1, "Malloc Error\n");
}

t_redirections	*all_together(int *i, t_cmds *cm, t_type type)
{
	t_redirections	*new;

	new = malloc(sizeof(t_redirections));
	if (!new)
		return (NULL);
	new->element = malloc(sizeof(char *) * 2);
	if (!new->element)
	{
		free(new);
		return (NULL);
	}
	new->mode = type;
	new->element[0] = ft_strdup(cm->args[*i]);
	split_str_del(cm->args, *i);
	if (!cm->args[*i])
		redi_checker(&new->element, cm->sh);
	else
	{
		new->element[1] = ft_strdup(cm->args[*i]);
		split_str_del(cm->args, *i);
	}
	info(new->element[0], GRN);
	info(new->element[1], GRN);
	new->next = NULL;
	return (new);
}

t_type	red_type_checker(char *str)
{
	t_type	final;

	final = FILE_NONE;
	if (str[0] == INFILE)
		final = FILE_IN_READ + (str[1] == INFILE);
	if (str[0] == OUTTRUC)
		final = 3 + (str[1] == OUTTRUC);
	return (final);
}

void	redirection_in(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	t_redirections	*new;
	t_redirections	*last;

	(void)sh;
	if (redi_node == FILE_NONE)
		return ;
	new = redi_new(i, node, redi_node);
	if (!new)
		return ;
	if (!node->infiles)
	{
		node->infiles = new;
		return ;
	}
	last = redirection_last_ptr(node->infiles);
	last->next = new;
}

void	redirection_out(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	t_redirections	*new;
	t_redirections	*last;

	(void)sh;
	if (redi_node == FILE_NONE)
		return ;
	new = redi_new(i, node, redi_node);
	if (!new)
		return ;
	if (!node->outfile)
	{
		node->outfile = new;
		return ;
	}
	last = redirection_last_ptr(node->outfile);
	last->next = new;
}
