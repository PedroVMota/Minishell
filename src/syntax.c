/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:55:52 by pedro             #+#    #+#             */
/*   Updated: 2023/09/22 08:56:41 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_next_char(char *input)
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

void	syntax_report(char *error, char *input, int size)
{
	int	i;

	i = -1;
	printf("Size: %d\n", size);
	write(2, "minishell: syntax error near unexpected token \'", 47);
	while (size && error[++i])
	{
		write(2, &error[i], 1);
		size--;
	}
	write(2, "\'\n", 2);
	if (input)
		free(input);
	g_shell.exit = 2;
	prompt();
}

void	syntax_sep(char *input, int i, int size)
{
	int	sep;
	int	temp;
	int	w;

	w = 0;
	temp = 0;
	sep = 0;
	if (input[i] == '|')
		sep = input[i];
	if (input[i] == '|' && input[i + 1] == '|')
		syntax_report("||", input, 2);
	else if (input[i] == '|' && !check_next_char(&input[i]))
		syntax_report("|", input, 1);
	else
		i += size;
	while (input[i])
	{
		if (((!sep && ft_valid_sep(&input[i], &temp)) || (sep
					&& ft_valid_sep(&input[i], &temp) == 4)) && !w)
			syntax_report(&input[i], input, temp);
		else if (input[i] != 32)
			w++;
		i++;
	}
	if (!w)
		syntax_report("newline", input, 8);
}

/*
	0 = index;
	1 = j
	2 = words
	3 = flags
	4 = seps
*/
void	ft_syntax_checker(char *in)
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
			syntax_sep(in, flags[0], flags[1]);
		else if ((in[flags[0]] == '\"' && !flags[3]) || (in[flags[0]] == '\''
				&& !flags[3]))
			syntax_quotes(in, flags[0], &flags[3]);
		else if (in[flags[0]] == flags[3])
			flags[3] = 0;
		else if (in[flags[0]] != 32)
			(flags[2])++;
		(flags[0]) += (flags[1] == 2);
		(flags[0])++;
	}
}
