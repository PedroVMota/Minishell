/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:47:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_split_size(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**split_append_new_split(char **arr, char **n_arr, int index)
{
	int		i;
	int		j;
	int		k;
	char	**new_arr;

	i = get_split_size(arr);
	j = get_split_size(n_arr);
	new_arr = (char **)malloc((i + j) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	k = -1;
	while (++k < index)
		new_arr[k] = strdup(arr[k]);
	k = -1;
	while (++k < j)
		new_arr[index + k] = strdup(n_arr[k]);
	k = index + 1;
	while (k < i)
	{
		new_arr[j + k - 1] = strdup(arr[k]);
		k++;
	}
	new_arr[i + j - 1] = NULL;
	free_split(arr, 0);
	return (new_arr);
}

void	parse(t_cmds *node, t_shell *sh)
{
	while (node)
	{
		redirection(node, sh);
		node = node->next;
	}
}
