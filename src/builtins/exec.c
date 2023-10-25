/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/25 14:33:04 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_cmds *node)
{
	standard_choiser(node);
	if (execve(node->args[0], node->args, NULL) == -1)
	{
		perror(node->args[0]);
        clean_commands(&node->sh->cmds);
		exit(1);
	}
	return (0);
}