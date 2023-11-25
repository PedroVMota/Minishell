/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:49:02 by pedro             #+#    #+#             */
/*   Updated: 2023/11/24 12:55:51 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		check_next_char(char *input);

void	syntax_report(char *error, char *input, int size, t_shell *sh)
{
	int	i;

	i = -1;
	write(2, "minishell: syntax error near unexpected token \'", 47);
	while (size && error[++i])
	{
		write(2, &error[i], 1);
		size--;
	}
	write(2, "\'\n", 2);
	if (input)
		free(input);
	sh->exit = 2;
	prompt(sh);
}

int	ft_valid_sep(char *in, int *data)
{
	data[0] = 0;
	if ((in[0] == '<' && in[1] == '<') || (in[0] == '>' && in[1] == '>'))
		data[0] = 2;
	else if (in[0] == '<' || in[0] == '>')
		data[0] = 1;
	else if (in[0] == '|')
		data[0] = 1;
	else if (in[0] == ';')
		data[0] = 1;
	if (in[0] == '|')
		return (4);
	return (data[0]);
}

void	check_syntax(char *input, int i, t_shell *sh)
{
	int	sep;
	int	temp;
	int	w;

	w = 0;
	temp = 0;
	sep = 0;
	if (((!sep && ft_valid_sep(&input[i], &temp)) || (sep
				&& ft_valid_sep(&input[i], &temp) == 4)) && !w)
		syntax_report(&input[i], input, temp, sh);
	else if (input[i] != 32)
		w++;
	if (!w)
		syntax_report("newline", input, 8, sh);
}

void	iterate_input(char *input, int i, int size, t_shell *sh)
{
	while (input[i])
	{
		check_syntax(input, i, sh);
		i += size;
	}
}

void	syntax_sep(char *input, int i, int size, t_shell *sh)
{
	if (input[i] == '|' && input[i + 1] == '|')
		syntax_report("||", input, 2, sh);
	else if (input[i] == '|' && !check_next_char(&input[i]))
		syntax_report("|", input, 1, sh);
	else
		iterate_input(input, i, size, sh);
}
