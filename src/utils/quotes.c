/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:04:07 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:31:06 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_quotes(char *input, int i, int *flag, t_shell *sh)
{
	char	c;

	c = input[i];
	*flag = c;
	while (input[++i])
	{
		if (c == input[i])
			return ;
	}
	syntax_report(&c, input, 1, sh);
}