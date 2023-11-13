/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/11/11 16:19:59 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void var_replacer(char **str, t_shell *sh)
{
	int varcounter;
	int varselector;
	int strselector;

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

static void reparcing(t_cmds *cmd)
{
	char **center[24];

	for (int i = 0; i < 24; i++)
		center[i] = NULL;
	for (int i = 0; cmd->args[i]; i++)
		switch_caracters(cmd->args[i]);
	for (int x = 0; cmd->args[x]; x++)
		center[x] = ft_split(cmd->args[x], ' ');
	for(int x = 0; x < 23; x++)
	{
		if(!center[x])
			continue;
	}
	print_split(cmd->args);
}

void parse(t_cmds *node, t_shell *sh)
{
	char **old;
	while (node)
	{
		var_replacer(node->args, sh);
		reparcing(node);
		redirection(node, sh);
		node = node->next;
	}
}
