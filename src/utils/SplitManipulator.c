/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SplitManipulator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:52:41 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:52:41 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Remove an element of a 2d matrix
/// @param arr the list
/// @param index the position that will be removed;
void	split_str_del(char **arr, int index)
{
	int	len;
	int	i;

	i = index - 1;
	len = 0;
	if (!arr || index < 0)
		return ;
	while (arr[len])
		len++;
	if (index >= len)
		return ;
	free(arr[index]);
	while (++i < len - 1)
		arr[i] = arr[i + 1];
	arr[len - 1] = NULL;
}

void	split_str_move(char ***src, int src_index, char ***dest, int dest_index)
{
	int	dest_len;
	int	src_len;

	dest_len = 0;
	src_len = 0;
	if (!*src || !*dest || src_index < 0 || dest_index < 0)
		return ;
	while (*src[src_len])
		src_len++;
	while (*dest[dest_len])
		dest_len++;
	if (src_index >= src_len || dest_index >= dest_len)
		return ;
	printf("%s Passing {%s} to %s\n", BLU, *src[src_index], RESET);
	(*dest)[dest_index] = (*src)[src_index];
	(*src)[src_index] = NULL;
}

void	split_str_replace(char **str, int index, char *new)
{
	int	len;

	len = 0;
	if (!str)
		return ;
	while (str[len])
		len++;
	if (index >= len)
		return ;
	if (str[index])
		free(str[index]);
	str[index] = new;
}

char	**split_str_copy(char **src)
{
	int		len;
	char	**dest;

	len = 0;
	if (!src)
		return (NULL);
	while (src[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = NULL;
	while (--len >= 0)
		dest[len] = ft_strdup(src[len]);
	return (dest);
}

char	**split_str_add(char **arr, char *str, int index)
{
	int		len;
	char	**new;
	int		i;

	i = -1;
	len = 0;
	if (!arr)
		return (NULL);
	while (arr[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	new[len + 1] = NULL;
	while (++i < index)
		new[i] = ft_strdup(arr[i]);
	new[i] = ft_strdup(str);
	while (++i <= len)
		new[i] = ft_strdup(arr[i - 1]);
	return (new);
}
