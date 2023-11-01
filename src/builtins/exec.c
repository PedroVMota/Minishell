/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:14:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 21:47:40 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_values(t_env **temp, int *count, char ***matrix)
{
	int	i;

	i = 0;
	while (i < *count)
	{
		if ((*temp)->vars[0] && (*temp)->vars[1])
		{
			(*matrix)[i] = malloc((strlen((*temp)->vars[0])
						+ strlen((*temp)->vars[1]) + 2) * sizeof(char));
			if (!(*matrix)[i])
				return (1);
			ft_strlcpy((*matrix)[i], (*temp)->vars[0],
				ft_strlen((*temp)->vars[0]) + 1);
			ft_strlcat((*matrix)[i], "=", ft_strlen((*matrix)[i]) + 2);
			ft_strlcat((*matrix)[i], (*temp)->vars[1],
				ft_strlen((*matrix)[i]) + strlen((*temp)->vars[1]) + 1);
		}
		(*temp) = (*temp)->next;
		i++;
	}
	return (0);
}

char	**list_2_matrix(t_env *env)
{
	int		count;
	t_env	*temp;
	char	**matrix;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	matrix = malloc((count + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	temp = env;
	if (pass_values(&temp, &count, &matrix))
		return (NULL);
	matrix[count] = NULL;
	return (matrix);
}

int	ft_exec(t_cmds *node)
{
	standard_choiser(node);
	if (execve(node->args[0], node->args, list_2_matrix(node->sh->env)) == -1)
	{
		perror(node->args[0]);
		clean_commands(&node->sh->cmds);
		exit(1);
	}
	return (0);
}
