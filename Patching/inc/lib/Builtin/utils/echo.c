/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 22:59:34 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_options(t_cmds *node, int *word)
{
	int break_line;

	break_line = 0;
	*word = 1;
	if (!node->args[1])
		return (0);
	if (node->args[*word][0] == '-' && node->args[*word][1] == 'n')
	{
		break_line = 1;
		(*word)++;
	}
	return (break_line);
}

int ft_echo(t_cmds *node)
{
	int word;
	int br;
	int *dups;

	redirect(node);
	dups = set_dups(node);
	if (!node->shouldrun)
		clean(node->sh, true, node->sh->exit, NULL);
	br = check_options(node, &word);
	while (node->args[word])
	{
		if (node->args[word])
			write(1, node->args[word], ft_strlen(node->args[word]));
		if (node->args[word + 1])
			write(1, " ", 1);
		word++;
	}
	if (br == 0)
		printf("\n");
	if (node->next || node->prev)
	{
		if (dups[0] != -10)
			close(dups[0]);
		if (dups[1] != -10)
			close(dups[1]);
		clean(node->sh, true, 0, NULL);
	}
	else
		close_redi(node);
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	free(dups);
	return (0);
}
