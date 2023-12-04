/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxChecker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:21:00 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/04 23:28:57 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirection_error_report(t_shell *sh, int *type, char *in, int *i);

void	syntax_pipe(char *in, int *i, t_shell *sh)
{
	if (in[*i + 1] == '|')
	{
		err_print("new unexpected token `||`");
		free(in);
		prompt(sh);
	}
	else if (pipe_analizer(in, i, sh))
	{
		err_print("new unexpected token `|`");
		free(in);
		prompt(sh);
	}
	(*i)++;
}

void	syntax_notsupported(char *in, int *i, t_shell *sh)
{
	if (in[*i] == ';')
	{
		err_print("new unexpected token `;`");
		free(in);
		prompt(sh);
	}
	else if (in[*i] == '\\')
	{
		err_print("new unexpected token  `\\`");
		free(in);
		prompt(sh);
	}
	(*i)++;
}

void	syntax_redirection(char *in, int *i, t_shell *sh)
{
	int		bi;
	char	c;
	int		type;

	c = in[*i];
	type = 1;
	bi = *i;
	if (in[*i] == '<' && in[*i + 1] == '<')
		type = 2;
	else if (in[(*i)] == '>' && in[(*i) + 1] == '>')
		type = 1;
	redirection_error_report(sh, &type, in, i);
}

void	ft_syntax_checker(char *in, t_shell *sh)
{
	int	index;
	int	len;

	len = ft_strlen(in);
	index = 0;
	while (index < len && in[index])
	{
		if (in[index] == '\'' || in[index] == '\"')
			skip_string_skip(in, &index, sh);
		else if (in[index] == '|')
			syntax_pipe(in, &index, sh);
		else if (in[index] == ';' || in[index] == '\\')
			syntax_notsupported(in, &index, sh);
		else if (in[index] == '<' || in[index] == '>')
			syntax_redirection(in, &index, sh);
		index++;
	}
}
