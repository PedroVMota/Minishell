/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:02:48 by pedro             #+#    #+#             */
/*   Updated: 2023/11/25 13:17:29 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int free_split(char **split, int ret)
{
	char **ptr;

	ptr = split;
	if (!split)
		return (1);
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
	return (ret);
}

static void close_fds(t_cmds *cmds)
{
	if (cmds->pipe[0] != -1)
		close(cmds->pipe[0]);
	if (cmds->pipe[1] != -1)
		close(cmds->pipe[1]);
	if (cmds->redirection[0] != -1)
		close(cmds->redirection[0]);
	if (cmds->redirection[1] != -1)
		close(cmds->redirection[1]);
}

int clean(t_shell *sh, bool _exit, int status, char *msg)
{
	t_cmds *cmds;
	t_cmds *tmp;

	tmp = NULL;
	cmds = NULL;
	if (sh)
		cmds = sh->cmds;
	while (sh && cmds)
	{
		close_fds(cmds);
		free_split(cmds->args, 1);
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	if (_exit)
	{
		if(msg)
			write(2, msg, ft_strlen(msg));
		ft_env_delete(&sh->env);
		exit(status);
	}
	return (0);
}

int ft_env_delete(t_env **env)
{
	t_env *tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free_split((*env)->vars, 1);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}
