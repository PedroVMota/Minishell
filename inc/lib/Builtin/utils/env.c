/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:52:13 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 18:17:25 by oharoon          ###   ########.fr       */
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

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int	ft_env(t_cmds *node)
{
	t_env	*env;
	int		*dups;

	redirect(node);
	dups = set_dups(node);
	env = node->sh->env;
	while (env)
	{
		if (env->has_equal)
			printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	if (node->next || node->prev)
		close_data(dups, node, true, 0);
	else
		close_data(dups, node, false, 0);
	return (0);
}
