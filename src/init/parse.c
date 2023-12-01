/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/12/01 19:27:36 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse(t_cmds *node, t_shell *sh)
{
	t_cmds	*command;

	command = node;
	while (command)
	{
		redirection(command, sh);
		command = command->next;
	}
}
