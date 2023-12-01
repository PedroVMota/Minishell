/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:52:13 by pedro             #+#    #+#             */
/*   Updated: 2023/11/30 00:50:11 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void close_files(t_cmds *node)
// {
// 	if (node->prev)
// 		close(node->prev->pipe[0]);
// 	if (node->pipe[0] != -1)
// 		close(node->pipe[0]);
// 	if (node->pipe[1] != -1)
// 		close(node->pipe[1]);
// 	if (node->redirection[0] != -1)
// 		close(node->redirection[0]);
// 	if (node->redirection[1] != -1)
// 		close(node->redirection[1]);
// }

// static bool outfile(t_cmds *node)
// {
// 	int fd;

// 	fd = -1;
// 	if (node->next)
// 		fd = node->pipe[1];
// 	if (node->redirection[1] != -1)
// 		fd = node->redirection[1];
// 	if (fd == -1)
// 		return (false);
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 		return (true);
// 	close_files(node);
// 	return (false);
// }

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int	ft_env(t_cmds *node)
{
	t_env	*env;
	t_shell	*head_master;

	if (file_descriptor_in(node))
		return (1);
	if (file_descriptor_out(node))
		return (1);
	head_master = node->sh;
	env = node->sh->env;
	while (env)
	{
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	if (node->next || node->prev)
		clean(head_master, true, 0, NULL);
	node->sh->exit = 0;
	return (0);
}
