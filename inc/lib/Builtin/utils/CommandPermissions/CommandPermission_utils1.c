/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPermission_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:55:14 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 01:00:05 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

bool	f_perm(char *name, char **paths)
{
	if (access(name, F_OK) == 0)
		return (free_split(paths, 1));
	return (false);
}

int	shell_update_exit_status_error(int _new_err, t_shell *sh)
{
	sh->exit = _new_err;
	return (sh->exit);
}

void	add_directory(char **cmd)
{
	int		i;
	char	*old_cmd;

	i = -1;
	while (cmd[++i])
	{
		old_cmd = cmd[i];
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			continue ;
		cmd[i] = ft_strjoin(cmd[i], "/");
		if (!cmd[i])
			return ;
		free(old_cmd);
	}
}
