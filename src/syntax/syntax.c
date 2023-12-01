/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:55:52 by pedro             #+#    #+#             */
/*   Updated: 2023/11/29 14:45:29 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		err_print("`;` caracter not supported (by the subject)");
		free(in);
		prompt(sh);
	}
	else if (in[*i] == '\\')
	{
		err_print("`\\`  caracter not supported (by the subject)");
		free(in);
		prompt(sh);
	}
	(*i)++;
}

void	syntax_redirection(char *in, int *i, t_shell *sh)
{
	if ((in[*i] == '<' || in[*i] == '>') && redi_ana(in, i, sh))
	{
		err_print("new unexpected token `newline'");
		free(in);
		prompt(sh);
	}
	else if ((in[*i + 1] == '<' || in[*i + 1] == '>') && redi_ana(in, i, sh))
	{
		err_print("new unexpected token `<<`");
		free(in);
		prompt(sh);
	}
	else if ((in[*i] == '<' && in[*i + 1] == '>') && redi_ana(in, i, sh))
	{
		if (in[*i] == '>')
			err_print("new unexpected token `>>`");
		else
			err_print("new unexpected token `<<`");
		free(in);
		prompt(sh);
	}
	(*i)++;
}

void	ft_syntax_checker(char *in, t_shell *sh)
{
	int	index;

	index = 0;
	while (in[index])
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
