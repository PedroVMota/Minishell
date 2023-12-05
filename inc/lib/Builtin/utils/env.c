/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:52:13 by pedro             #+#    #+#             */
/*   Updated: 2023/12/04 22:59:34 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int ft_env(t_cmds *node)
{
	t_env *env;
	t_shell *head_master;
	int *dups;
	redirect(node);
	dups = set_dups(node);
	head_master = node->sh;
	env = node->sh->env;
	while (env)
	{
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	if (node->next || node->prev)
	{
		if (dups[0] != -10)
			close(dups[0]);
		if (dups[1] != -10)
			close(dups[1]);
		clean(head_master, true, 0, NULL);
	}
	else
		close_redi(node);
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	node->sh->exit = 0;
	free(dups);
	return (0);
}
