/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:56:28 by pedro             #+#    #+#             */
/*   Updated: 2023/09/26 08:44:53 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Remove an element of a 2d matrix
/// @param arr the list
/// @param index the position that will be removed;
void	remove_element(char **arr, int index)
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

void	move_element(char **src, int src_index, char **dest, int dest_index)
{
	int	dest_len;
	int	src_len;

	dest_len = 0;
	src_len = 0;
	if (!src || !dest || src_index < 0 || dest_index < 0)
		return ;
	while (src[src_len])
		src_len++;
	while (dest[dest_len])
		dest_len++;
	if (src_index >= src_len || dest_index >= dest_len)
		return ;
	dest[dest_index] = src[src_index];
	src[src_index] = NULL;
}