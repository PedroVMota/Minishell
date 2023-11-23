/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:33 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/23 22:51:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmds *node)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		perror("getcwd() error");
		if (node->next)
			clean(node->sh, true, 1, NULL);
		return (1);
	}
	(void)node;
	return (0);
}
