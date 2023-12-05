/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:29:28 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/04 23:30:11 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	err_print(char *msg)
{
	ft_putstr_fd("minishell: Syntax error: ", 2);
	ft_putendl_fd(msg, 2);
}

// SECTION - SKIP STRING SKIP
void	skip_string_skip(char *in, int *i, t_shell *sh)
{
	char	c;
	bool	syntax_error;

	syntax_error = false;
	c = in[*i];
	(*i)++;
	while (in[*i] != c)
	{
		if (in[*i] == '\0')
		{
			syntax_error = true;
			break ;
		}
		(*i)++;
	}
	if (syntax_error)
	{
		if (c == '\'')
			err_print("new unexpected token `\'`");
		else
			err_print("new unexpected token `\"`");
		free(in);
		prompt(sh);
	}
}

// SECTION - PIPE ANALIZER
bool	pipe_analizer(char *in, int *i, t_shell *sh)
{
	if (in[*i + 1])
		(*i)++;
	while (in[*i])
	{
		if (ft_isalnum(in[*i]))
			return (false);
		else if (in[*i] == '|')
			return (true);
		else if (in[*i] == '\'' || in[*i] == '\"')
		{
			skip_string_skip(in, i, sh);
			return (false);
		}
		(*i)++;
	}
	return (true);
}

// SECTION - REDIRECTIONS ANALIZER
bool	redi_ana(char *in, int *i, t_shell *sh)
{
	if (in[*i] == '<' && in[*i + 1] == '<')
		(*i) = (*i) + 2;
	else if (in[(*i)] == '>' && in[(*i) + 1] == '>')
		(*i) = (*i) + 2;
	else
		(*i)++;
	while (in[*i])
	{
		if (ft_isalnum(in[*i]))
			return (false);
		else if (in[*i + 1] == '|')
			return (true);
		else if (in[*i] == '\'' || in[*i] == '\"')
		{
			skip_string_skip(in, i, sh);
			return (false);
		}
		(*i)++;
	}
	return (true);
}
