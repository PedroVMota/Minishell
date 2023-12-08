/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:20:20 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

static int	check_options(t_cmds *node, int *word)
{
	int	break_line;
	int	i;

	break_line = 0;
	i = 1;
	*word = 1;
	if (!node->args[1])
		return (0);
	while (node->args[*word] && node->args[*word][0] == '-'
		&& node->args[*word][1] != '-')
	{
		while (node->args[*word][i] == 'n')
		{
			if (node->args[*word][i + 1])
				if (node->args[*word][i + 1] != 'n')
					return (0);
			i++;
		}
		i = 1;
		break_line = 1;
		(*word)++;
	}
	return (break_line);
}

static void	close_data(int *dups, t_cmds *node, bool exit)
{
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	close_redi(node);
	free(dups);
	if (exit)
		clean(node->sh, true, 0, NULL);
}

int	ft_echo(t_cmds *node)
{
	int	word;
	int	br;
	int	*dups;

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
		close_data(dups, node, true);
	else
		close_data(dups, node, false);
	return (0);
}
