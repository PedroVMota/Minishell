/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:05:29 by pedro             #+#    #+#             */
/*   Updated: 2023/11/06 20:53:36 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char replace(char c)
{
	if (c <= 0)
		return (c);
	else if (c > 127)
		return (c);
	if (c == '|')
		return ('\3');
	if (c == '>')
		return ('\6');
	if (c == '<')
		return ('\7');
	if (c == ' ')
		return ('\4');
	if (c == '\"')
		return ('\1');
	if (c == '\'')
		return ('\1');
	return (c);
}

void inside_string_skip(char *beg, int *pos, bool *change)
{
	char whatChar;

	whatChar = 0;
	if (beg[*pos] == '\"' || beg[*pos] == '\'')
	{
		whatChar = beg[*pos];
		beg[*pos] = replace(beg[*pos]);
		*change = !(*change);
	}
	if (!*change)
	{
		while (beg[*pos])
		{
			if(beg[*pos] == whatChar)
			{
				beg[*pos] = replace(beg[*pos]);
				*change = !(*change);
				break;
			}
			(*pos)++;
		}
	}
}

void switch_caracters(char *ptr)
{
	int main = 0;
	bool change = true;
	while (ptr[main])
	{
		inside_string_skip(ptr, &main, &change);
		if(change)
			ptr[main] = replace(ptr[main]);
		main++;
	}
}
