/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:38:59 by pedro             #+#    #+#             */
/*   Updated: 2023/10/01 10:52:57 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_typeschecker
{
	FILE_NONE,
	FILE_IN_READ,
	FILE_IN_HEREDOC,
	FILE_OUT_TRUNC,
	FILE_OUT_APPEND,
}		t_type;

t_type	red_type_checker(char *str)
{
	t_type	final;

	final = FILE_NONE;
	if (str[0] == TOKEN_IN)
		final = FILE_IN_READ + (str[0] == TOKEN_IN);
	if (str[0] == TOKEN_OUT)
		final = 3 + (str[1] == TOKEN_OUT);
	return (final);
}

void	close_prev_fd(t_type mode, t_cmds *node, int *i)
{
	if (mode != FILE_NONE)
		remove_element(node->args, *i);
	if (mode == FILE_IN_READ || mode == FILE_IN_HEREDOC)
	{
		close(node->redirection[0]);
		node->redirection[0] = -1;
	}
	if (mode == FILE_OUT_TRUNC || mode == FILE_OUT_APPEND)
	{
		close(node->redirection[1]);
		node->redirection[1] = -1;
	}
}

void	make_redirection(t_type type, t_cmds *node, int *i)
{
	close_prev_fd(type, node, i);
	if (type == FILE_IN_READ)
	{
		node->redirection[0] = open(node->args[*i], O_RDONLY);
		if (node->redirection[0] == 1)
			write(1, "Open() Error\n", 14);
	}
	if (type == FILE_IN_HEREDOC)
		heredoc(node, node->args[*i]);
	if (type == FILE_OUT_TRUNC)
	{
		node->redirection[1] = open(node->args[*i], O_CREAT | O_RDWR,
				O_TRUNC | 0644);
		if (node->redirection[1] == 1)
			write(1, "Open() Error\n", 14);
	}
	if (type == FILE_OUT_APPEND)
	{
		node->redirection[1] = open(node->args[*i], O_CREAT | O_RDWR,
				O_APPEND | 0644);
		if (node->redirection[1] == 1)
			write(1, "Open() Error\n", 14);
	}
	if (type != FILE_NONE)
		remove_element(node->args, *i);
}

void	redirection(t_cmds *node)
{
	char	**args;
	t_type	red_mode;
	int		i;

	red_mode = FILE_NONE;
	i = -1;
	args = node->args;
	while (args[++i])
	{
		remove_quotes(args[i]);
		red_mode = red_type_checker(args[i]);
		make_redirection(red_mode, node, &i);
	}
}
