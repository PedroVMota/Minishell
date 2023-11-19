/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/19 19:56:58 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void outfile(t_cmds *node)
{
	int fd;

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

static int check_options(t_cmds *node, int *word)
{
	int break_line;

	break_line = 0;
	*word = 1;
	if (!node->args[1])
	{
		write(1, "\n", 1);
	}
	if (node->args[*word][0] == '-' && node->args[*word][1] == 'n')
	{
		break_line = 1;
		(*word)++;
	}
	return break_line;
}

int ft_echo(t_cmds *node)
{
	int i;
	int word;
	int br;

	i = 0;
	br = check_options(node, &word);
	outfile(node);
	while (node->args[word])
	{
		write(1, node->args[word], ft_strlen(node->args[word]));
		if (node->args[word + 1])
			write(1, " ", 1);
		word++;
	}
	if (br == 0)
		printf("\n");
	return (0);
}
