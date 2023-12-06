/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:33 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 05:49:29 by pedro            ###   ########.fr       */
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

int	ft_pwd(t_cmds *node)
{
	char	path[1024];
	int		*dups;

	dups = NULL;
	redirect(node);
	dups = set_dups(node);
	if (!node->shouldrun)
		clean(node->sh, true, node->sh->exit, NULL);
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		perror("getcwd() error");
		close_data(dups, node, true, 1);
	}
	close_data(dups, node, false, 0);
	return (0);
}
