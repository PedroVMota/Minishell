/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPermission_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:58:18 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/04 21:59:08 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int *set_dups(t_cmds *node)
{
	int	fdi;
	int	fdo;
	int	*du = malloc(4 * 2);
	if (!du)
		clean(node->sh, true, 1, "Malloc Error\n");
	du[0] = -10;
	du[1] = -10;
	fdi = -4;
	fdo = -4;
	if (node->prev)
		fdi = node->prev->pipe[0];
	if (node->redirection[0] != -1 && node->redirection[0] != -2)
		fdi = node->redirection[0];
	if (node->next)
		fdo = node->pipe[1];
	if (node->redirection[1] != -1 && node->redirection[1] != -2)
		fdi = node->redirection[1];
	if (fdi != -4)
		du[0] = dup2(fdi, STDIN_FILENO);
	if (fdo != -4)
		du[1] = dup2(fdo, STDOUT_FILENO);
	return (du);
}