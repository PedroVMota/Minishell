/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:05:29 by pedro             #+#    #+#             */
/*   Updated: 2023/11/04 12:02:57 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_mode_changer_ascii(char set, t_mode *stat);

char	replace(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (OUTTRUC);
	if (c == '<')
		return (INFILE);
	if (c == ';')
		return (SEMI_COLOM);
	if (c == ' ')
		return (SPACE);
	if (c == '\"')
		return (DQUOTE);
	if (c == '\'')
		return (QUOTE);
	return (c);
}

void	switch_caracters(char *ptr)
{
	t_mode	arr[2];
	int		i;

	i = -1;
	arr[0] = ENV_MODE_TOKEN;
	arr[1] = ENV_MODE_TOKEN;
	if (!ptr)
		return ;
	while (ptr[++i])
	{
		arr[1] = arr[0];
		ft_mode_changer_ascii(ptr[i], &arr[0]);
		if ((arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_TOKEN))
			ptr[i] = replace(ptr[i]);
		else if ((arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_DQUOTE)
			|| (arr[0] == ENV_MODE_DQUOTE && arr[1] == ENV_MODE_TOKEN))
			ptr[i] = replace(ptr[i]);
		else if ((arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_QUOTE)
			|| (arr[0] == ENV_MODE_QUOTE && arr[1] == ENV_MODE_TOKEN))
			ptr[i] = replace(ptr[i]);
		else if ((arr[0] != ENV_MODE_TOKEN && arr[1] != ENV_MODE_TOKEN))
			continue;
	}

}
