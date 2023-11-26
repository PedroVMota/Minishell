/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:47:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
void ShowCommands(t_cmds *cmd);

void parse(t_cmds *node, t_shell *sh)
{
	t_cmds *command;

	command = node;
	while (command)
	{
		redirection(command, sh);
		command = command->next;
	}
	ShowCommands(node);
}
