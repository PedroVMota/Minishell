/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:33 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 22:59:34 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmds *node)
{
	char	path[1024];
	int *dups;

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
		if (node->next)
			clean(node->sh, true, 1, NULL);
		else
			close_redi(node);
		return (1);
	}
	(void)node;
	close_redi(node);
	if(dups[0] != -10)
		close(dups[0]);
	if(dups[1] != -10)
		close(dups[1]);
	free(dups);
	return (0);
}
