/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:03 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 06:05:58 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

static void	close_data(int *dups, t_cmds *node, bool exit, int status)
{
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	close_redi(node);
	free(dups);
	if (exit)
		clean(node->sh, true, status, NULL);
}

static long long	count_args(char **s)
{
	long long	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_exit(t_cmds *node)
{
	long long	newexit;
	int			*dups;

	if (!node->args[1])
		clean(node->sh, true, 0, NULL);
	newexit = ft_atoi(node->args[1]);
	redirect(node);
	dups = set_dups(node);
	if (newexit > INT_MAX)
	{
		write(2, "Minishell: exit: Numeric argument required\n", 44);
		close_data(dups, node, true, 1);
	}
	if (newexit < 0)
		newexit = 255 + (newexit);
	if (count_args(node->args) > 2)
	{
		write(2, "Minishell: exit: Too many arguments\n", 36);
		close_data(dups, node, true, 1);
	}
	if (node->args[1])
		close_data(dups, node, true, newexit);
	return (0);
}
