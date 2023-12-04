/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:03 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/23 22:49:24 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long count_args(char **s)
{
	long long i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int ft_exit(t_cmds *node)
{
	long long newexit = ft_atoi(node->args[1]);
	int *dups;

	redirect(node);
	dups = set_dups(node);
	if (newexit > INT_MAX)
		clean(node->sh, true, 2, "Minishell: exit: Numeric argument required\n");
	if (newexit < 0)
		newexit = 255 + (newexit);
	if (count_args(node->args) > 1)
		clean(node->sh, true, 2, "Minishell: exit: Too many arguments\n");
	if (node->args[1])
		clean(node->sh, true, ft_atoi(node->args[1]), NULL);
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	clean(node->sh, true, 0, NULL);

	return (0);
}
