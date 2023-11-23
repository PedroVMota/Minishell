/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/23 22:48:30 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_cmds *node)
{
	standard_choiser(node);
	if (execve(node->args[0], node->args, node->sh->envp) == -1)
		clean(node->sh, true, node->sh->exit, NULL);
	return (0);
}
