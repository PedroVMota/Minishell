/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelperFunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:52:24 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 12:06:11 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isbuiltin(t_cmds *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (false);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (true);
	return (false);
}

bool	isallwhitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
