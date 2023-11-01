/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:08:35 by pedro             #+#    #+#             */
/*   Updated: 2023/09/25 12:16:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE || str[i] == QUOTE)
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

/// @brief Check position index of the variable
/// @param ptr string that will be searched
/// @return return a integer if exit otherwise -1
int	var_pos(char *ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		if (ptr[index] == QUOTE)
			return (-1);
		if (ptr[index] == '$' && ptr[index + 1] != '?')
			return (index);
		index++;
	}
	return (-1);
}
