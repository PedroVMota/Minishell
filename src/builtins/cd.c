/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:43 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 16:02:33 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_part_str(char *str, const char *remove)
{
	char *pos = strstr(str, remove);
	if (pos != NULL) {
		ft_memmove(pos, pos + strlen(remove), strlen(pos + strlen(remove)) + 1);
	}
}

int	ft_cd(t_cmds *node)
{
//OLDPWD working, but need to change oldpwd, it doesnt change for some reason

	if (!node->args || !node->args[0])
	{
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(node->args[0], "cd", 2))
	{
		if (!node->args[1])
			chdir(getenv("HOME"));
		else if (node->args[2])
		{
			printf("cd: too many arguments\n");
			return (1);
		}
		else if (node->args[1][0] == '~')
		{
			chdir(getenv("HOME"));
			if (node->args[1][1])
			{
				remove_part_str(node->args[1], "~/");
				if (chdir(node->args[1]))
					printf("error changing directory\n");
			}
			return (1);
		}
		else if (node->args[1][0] == '-')
		{
			if (chdir(getenv("OLDPWD")))
				printf("error changing directory\n");
			return (1);
		}
		else
		{
			if (chdir(node->args[1]))
				printf("error changing directory\n");
		}
		return (1);
	}
	return (0);
}