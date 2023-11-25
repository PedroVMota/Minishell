/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:35:34 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 11:24:19 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	return (NULL);
}

bool	does_have_var(char *s)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	while (s[index])
	{
		if (s[index] == '\'' && quote == 0)
			quote = s[index];
		else if (s[index] == '\'' && quote != 0)
			quote = 0;
		else if (s[index] == '$' && !quote)
			return (true);
		index++;
	}
	return (false);
}

int	varlib_start_position(char *ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		if (ptr[index] == QUOTE)
			return (-1);
		if (ptr[index] == '$' && ptr[index + 1] != '$')
			return (index);
		index++;
	}
	return (-1);
}
