/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/26 18:12:48 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_cmds *node)
{
	// standard_choiser(node);
	if (execve(node->args[0], node->args, node->sh->envp))
	{
		perror(node->args[0]);
		// clean_commands(&node->sh->cmds);
		clean(node->sh, true, errno, NULL);
		exit(1);
	}
	return (0);
}
