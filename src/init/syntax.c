/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:55:52 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:55:52 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_report(char *error, char *input, int size, t_shell *sh);
int		ft_valid_sep(char *in, int *data);
void	syntax_sep(char *input, int i, int size, t_shell *sh);

int	check_next_char(char *input)
{
	int	i;

	if (!input || !(*input))
		return (0);
	i = -1;
	while (input[++i])
	{
		if (ft_isalnum(input[i]))
			return (1);
		if (input[i] == '<' || input[i] == '>' || input[i] == ';')
			return (0);
	}
	return (0);
}

void	ft_syntax_checker(char *in, t_shell *sh)
{
	int	flags[5];
	int	i;

	i = 0;
	while (i <= 4)
		flags[i++] = 0;
	if (!in)
		return ;
	while (in[flags[0]])
	{
		if ((in[flags[0]] == '\'' || in[flags[0]] == '\"') && (!flags[4]
				|| flags[4] == in[flags[0]]))
			flags[4] = (in[flags[0]]) * (flags[4] != in[flags[0]]);
		if (!flags[4] && ft_valid_sep(&in[flags[0]], &(flags[1])))
			syntax_sep(in, flags[0], flags[1], sh);
		else if ((in[flags[0]] == '\"' && !flags[3]) || (in[flags[0]] == '\''
				&& !flags[3]))
			syntax_quotes(in, flags[0], &flags[3], sh);
		else if (in[flags[0]] == flags[3])
			flags[3] = 0;
		else if (in[flags[0]] != 32)
			(flags[2])++;
		(flags[0]) += (flags[1] == 2);
		(flags[0])++;
	}
}
