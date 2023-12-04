/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 23:13:35 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool checker(t_cmds *node)
{
	int perm[2];
	permission_tester(node, perm);
	if (perm[0] == 127 && perm[1] == 2)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return 127;
	}
	else if (perm[0] == 127 && perm[1] == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		return 127;
	}
	else if (perm[0] == 126)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": Permission Denied\n", 2);
		return 126;
	}
	return (0);
}

int ft_exec(t_cmds *node)
{
	int *dups;
	info("Exec", YEL);
	redirect(node);
	dups = set_dups(node);

	if (checker(node) == true)
	{
		free(dups);
		clean(node->sh, true, node->sh->exit, NULL);
	}
	printf("[%s]\n", node->args[0]);
	info("Passed the file or command permissions", GRN);
	clean_redirection(&node->infiles);
	clean_redirection(&node->outfile);
	free(dups);
	if (execve(node->args[0], node->args, node->sh->envp))
	{
		ft_putstr_fd(strerror(errno), 2);
		clean(node->sh, true, errno, NULL);
	}
	return (0);
}
