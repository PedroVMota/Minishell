/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:52:30 by pedro             #+#    #+#             */
/*   Updated: 2023/11/11 16:19:59 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int getSplitSize(char **str)
{
	int i;

	i = 0;
	if (!str)
		return 0;
	while (str[i])
		i++;
	return i;
}

char **split_append_new_split(char **arr, char **n_arr, int index)
{
	int i = 0, j = 0, k = 0;
	i = getSplitSize(arr);
	j = getSplitSize(n_arr);
	char **new_arr = (char **)malloc((i + j) * sizeof(char *));
	if (new_arr == NULL)
		return NULL;
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
	return new_arr;
}
char *join_str(char **arr, char delimiter);

void parse(t_cmds *node, t_shell *sh)
{
	char **old;
	while (node)
	{
		redirection(node, sh);
		node = node->next;
	}
}
