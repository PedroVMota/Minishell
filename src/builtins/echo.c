/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:09 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 15:12:03 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmds *node)
{
    int i;
	int	word;

	word = 1;
    i = 0;
    if (!ft_strncmp(node->args[0], "echo", ft_strlen("echo")))
	{
		int break_line = 0;
		if (!node->args[1])
		{
			printf("\n");
			return (1);
		}
		else 
		{
			if (node->args[word][i] == '-' && node->args[word][i+1] == 'n')
			{
				break_line = 1;
				i = 0;
				word++;
			}
			while(node->args[word])
			{
				while(node->args[word][i])
				{
					if (node->args[word][i] == '$' && node->args[word][i + 1] == '?')
					{
						printf("%d", node->sh->exit);
						i += 2;
					}
					else
					{
						printf("%c",node->args[word][i]);
						i++;
					}
				}
				printf(" ");
				word++;
				i = 0;
			}
			if (break_line == 0)
				printf("\n");
			return (1);
		}
    }
	return (0);
}