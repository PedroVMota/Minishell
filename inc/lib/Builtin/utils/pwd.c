/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:33 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/02 14:51:19 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmds *node)
{
	char	path[1024];

	redirect(node);
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
	return (0);
}
