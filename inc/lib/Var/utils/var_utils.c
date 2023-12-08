/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 04:56:45 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 13:48:03 by pedro            ###   ########.fr       */
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

void	update_quote(int *quote, char *s, int *index)
{
	if (s[*index] == '\'' && *quote == 0)
		*quote = 1;
	else if (s[*index] == '\'' && *quote == 1)
		*quote = 0;
	else if (s[*index] == '\"' && *quote == 0)
		*quote = 2;
	else if (s[*index] == '\"' && *quote == 2)
		*quote = 0;
}

bool	does_have_var(char *s)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	if (!s)
		return (false);
	while (s[index])
	{
		update_quote(&quote, s, &index);
		if (s[index] == '$' && quote != 1)
			return (true);
		index++;
	}
	return (false);
}

int	varlib_start_position(char *ptr)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		update_quote(&quote, ptr, &index);
		if (ptr[index] == '$' && ptr[index + 1] != '$' && quote != 1)
			return (index);
		index++;
	}
	return (-1);
}

void	*trash(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	return (NULL);
}
