/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:52:13 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 14:48:03 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int	ft_env(t_cmds *node)
{
	t_env	*env;
	t_shell	*head_master;

	redirect(node);
	head_master = node->sh;
	env = node->sh->env;
	while (env)
	{
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	if (node->next || node->prev)
		clean(head_master, true, 0, NULL);
	else
		close_redi(node);
	node->sh->exit = 0;
	return (0);
}
