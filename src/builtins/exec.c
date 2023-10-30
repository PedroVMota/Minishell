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

char **list_2_matrix(t_env *env)
{
    int count;
    t_env *temp;
	int i;

	i = 0;
	count = 0;
	temp = env;
    while (temp)
	{
        count++;
        temp = temp->next;
    }
    char **matrix = malloc((count + 1) * sizeof(char *));
    if (!matrix)
        return NULL;
    temp = env;
    while (i < count)
	{
        if (temp->vars[0] && temp->vars[1])
		{
            matrix[i] = malloc((strlen(temp->vars[0]) + strlen(temp->vars[1]) + 2) * sizeof(char));
            if (!matrix[i]) {
                return NULL;
            }
            strcpy(matrix[i], temp->vars[0]);
            strcat(matrix[i], "=");
            strcat(matrix[i], temp->vars[1]);
        }
        temp = temp->next;
		i++;
    }
    matrix[count] = NULL;
    return matrix;
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