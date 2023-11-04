/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 09:17:12 by pedro             #+#    #+#             */
/*   Updated: 2023/11/04 11:03:40 by pedromota        ###   ########.fr       */
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
	{
		free(input);
		return (1);
	}
	return (0);
}


static bool convert_data(char **text, char *delimiter, t_shell *sh, int fd)
{
	int varcounter;
	int varselector;

	varselector = 0;
	if(!*text || !delimiter)
		return true;
	if (check_elements(*text, delimiter))
		return true ;
	varcounter = variable_counter(*text);
	while (varselector < varcounter)
	{
		*text = varcheckvalid(*text, sh);
		varselector++;
	}
	write(fd, *text, ft_strlen(*text));
	free(*text);
	return false;
}

void	heredoc(t_cmds *node, char *delimiter)
{
	char	*text;
	int		bytes_read;
	int		here_doc[2];

	text = NULL;
	if (pipe(here_doc) == -1)
		return ;
	node->redirection[0] = here_doc[0];
	bytes_read = 1;
	while (bytes_read > -1 && node->sh->stop != 1)
	{
		write(1, "Here_doc >", 11);
		text = get_next_line(0);
		if(convert_data(&text, delimiter, node->sh, here_doc[1]))
			break;
	}
	free(text);
	close(here_doc[1]);
}
