/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/29 21:51:19 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile(t_cmds *node)
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

static int	check_options(t_cmds *node, int *word)
{
	int	break_line;

	break_line = 0;
	*word = 0;
	if (!node->args[1])
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (node->args[*word][0] == '-' && node->args[*word][1] == 'n')
	{
		break_line = 1;
		(*word)++;
	}
	return (break_line);
}

int	ft_echo(t_cmds *node)
{
	int	i;
	int	word;
	int	br;

	i = 0;
	br = check_options(node, &word);
	word++;
	outfile(node);
	while (node->args[word])
	{
		while (node->args[word][i])
		{
			if (node->args[word][i] == '$' && node->args[word][i + 1] == '?')
				i += printf("%d", node->sh->exit) + 1;
			else
				i += write(1, node->args[word], ft_strlen(node->args[word]));
		}
		printf(" ");
		word++;
		i = 0;
	}
	if (br == 0)
		printf("\n");
	exit(1);
	return (0);
}
