/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                 +#+  +:+
	+#+        */
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
}			t_type;

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

static void	check_permissions(char *filename, t_type mode, t_shell *sh)
{
	if (!filename && mode != FILE_NONE)
	{
		write(2, "Minishell: ", 12);
		perror(filename);
		// write(2, "Minishell: No such File or Directory\n", 38);
		return ;
	}
	else if (access(filename, F_OK) == -1 && mode != FILE_NONE
		&& mode != FILE_OUT_APPEND && mode != FILE_OUT_TRUNC)
	{
		write(2, "Minishell: ", 12);
		perror(filename);
		// write(2, "Minishell: ", 12);
		// write(2, filename, ft_strlen(filename));
		// write(2, ": No such file or directory\n", 29);
	}
	else if ((mode == FILE_IN_READ) && access(filename, R_OK) == -1)
	{
		write(2, "Minishell: ", 12);
		perror(filename);
		sh->exit = 1;
	}
}

void	close_prev_fd(t_type mode, t_cmds *node, int *i)
{
	if (mode != FILE_NONE)
		split_str_del(node->args, *i);
	if (mode == FILE_IN_READ || mode == FILE_IN_HEREDOC)
	{
		if (node->redirection[0] != -1)
			close(node->redirection[0]);
		node->redirection[0] = -1;
	}
	if (mode == FILE_OUT_TRUNC || mode == FILE_OUT_APPEND)
	{
		if (node->redirection[1] != -1)
			close(node->redirection[1]);
		node->redirection[1] = -1;
	}
	if(mode == FILE_IN_READ)
		check_permissions(node->args[*i], mode, node->sh);
}

void	make_redirection(t_type type, t_cmds *node, int *i, t_shell *sh)
{
	close_prev_fd(type, node, i);
	if (type == FILE_IN_READ)
		node->redirection[0] = open(node->args[*i], O_RDONLY);
	else if (type == FILE_IN_HEREDOC)
	{
		sh->hd = 1;
		heredoc(node, node->args[*i]);
		split_str_del(node->args, *i);
	}
	else if (type == FILE_OUT_TRUNC)
		node->redirection[1] = open(node->args[*i], O_CREAT | O_RDWR | O_TRUNC,
			0644);

	else if (type == FILE_OUT_APPEND)
		node->redirection[1] = open(node->args[*i],
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != FILE_NONE)
		split_str_del(node->args, *i);
}

void	redirection(t_cmds *node, t_shell *sh)
{
	char	**args;
	t_type	red_mode;
	int		i;

	red_mode = FILE_NONE;
	i = 0;
	args = node->args;
	while (args[i])
	{
		remove_quotes(args[i]);
		red_mode = red_type_checker(args[i]);
		make_redirection(red_mode, node, &i, sh);
		if (red_mode == FILE_NONE)
			i++;
	}
}
