/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/10/02 14:07:36 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	var_replacer(char **str)
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
			str[strselector] = varcheckvalid(str[strselector]);
			varselector++;
		}
		strselector++;
	}
}

void	parse(t_cmds *node)
{
	while (node)
	{
		var_replacer(node->args);
		redirection(node);
		node = node->next;
	}
}
