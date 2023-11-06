/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/11/05 18:54:06 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	var_replacer(char **str, t_shell *sh)
{
	int	varcounter;
	int	varselector;
	int	strselector;

	varselector = 0;
	varcounter = 0;
	strselector = 0;
	while (str[strselector])
	{
		varcounter = variable_counter(str[strselector]);
		varselector = 0;
		while (varselector < varcounter)
		{
			str[strselector] = varcheckvalid(str[strselector], sh);
			varselector++;
		}
		strselector++;
	}
}

void	parse(t_cmds *node, t_shell *sh)
{
	while (node)
	{
		var_replacer(node->args, sh);
		redirection(node, sh);
		node = node->next;
	}
}
