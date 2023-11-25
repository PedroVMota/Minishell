/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/25 13:25:29 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void close_fd_cmd(t_cmds *node)
{
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

static void outfile(t_cmds *node)
{
	int fd;

	fd = -1;
	if (node->next)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	if (fd == -1)
		return;
	if (dup2(fd, 1) == -1)
	{
		write(2, "Minishell: ", 12);
		perror("dup2");
		exit(1);
	}
	close_fd_cmd(node);
}

static int check_options(t_cmds *node, int *word)
{
	int break_line;

	break_line = 0;
	*word = 1;
	if (!node->args[1])
		write(1, "\n", 1);
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

	outfile(node);
	if (node->shouldrun == 0)
	{
		printf("Here\n");
		return 1;
	}
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
		clean(node->sh, true, 0, NULL);
	return (0);
}