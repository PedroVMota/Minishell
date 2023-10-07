/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 09:17:12 by pedro             #+#    #+#             */
/*   Updated: 2023/10/02 14:07:36 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_elements(char *input, char *target)
{
	int	target_len;
	int	input_len;

	target_len = ft_strlen(target);
	input_len = ft_strlen(input) - 1;
	if (ft_strncmp(input, target, target_len) == 0 && input_len == target_len)
		return (1);
	return (0);
}



void	heredoc(t_cmds *node, char *delimiter)
{
	char	*text;
	int		bytes_read;
	int		here_doc[2];

	text = NULL;
	if (pipe(here_doc) == -1)
	{
		write(2, "Pipe Error\n", 12);
		return ;
	}
	node->redirection[0] = here_doc[0];
	bytes_read = 1;
	while (bytes_read > -1)
	{
		write(1, "Here_doc >", 11);
		text = get_next_line(0);
		if (!text)
		{
			free(text);
			continue ;
		}
		if (check_elements(text, delimiter))
			break ;
		write(here_doc[1], text, ft_strlen(text));
		free(text);
	}
	close(here_doc[1]);
}
