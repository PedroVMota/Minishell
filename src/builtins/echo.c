/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:10 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 19:08:35 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	env_sizer(int start_index, char *str)
// {
// 	int	i = start_index;
// 	while ((str[i] != ' ' || str[i] != '	') && str[i])
// 		i++;
// 	return (i - start_index);
// }

// char	*ft_str_toupper(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] > 96 && str[i] < 123)
// 			str[i] -= 32;
// 		i++;
// 	}
// 	return (str);
// }

int builtin_echo(t_cmds *node)
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