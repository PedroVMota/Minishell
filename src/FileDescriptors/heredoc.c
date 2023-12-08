/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:48:47 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 18:30:33 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_elements(char *input, char *target)
{
	if (!ft_strcmp(input, target))
	{
		free(input);
		return (1);
	}
	return (0);
}

static bool	convert_data(char **text, char *delimiter, t_shell *sh, int fd)
{
	if (!*text || !delimiter)
		return (true);
	*text = varlib_execute(*text, sh);
	if (check_elements(*text, delimiter))
		return (true);
	if (write(fd, *text, ft_strlen(*text)) == -1)
	{
		free(*text);
		return (true);
	}
	write(fd, "\n", 1);
	free(*text);
	return (false);
}

void	heredoc(t_cmds *node, char *delimiter, int fdo)
{
	char	*text;
	int		bytes_read;

	text = NULL;
	bytes_read = 1;
	while (bytes_read > -1 && node->sh->stop != 1)
	{
		text = readline("➡️  ");
		if (convert_data(&text, delimiter, node->sh, fdo))
			break ;
	}
	close(fdo);
	if (g_signal_status == SIGNAL_EXIT_HD)
		clean(node->sh, true, 130, NULL);
	clean(node->sh, true, 0, NULL);
}
