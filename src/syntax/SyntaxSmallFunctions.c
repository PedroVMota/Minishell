/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxSmallFunctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:30:30 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/04 23:32:36 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirection_error_report(t_shell *sh, int *type, char *in, int *i)
{
	int		bi;
	char	c;

	c = in[*i];
	bi = *i;
	if (*type == 2 && redi_ana(in, &bi, sh))
	{
		err_print("new unexpected token `newline'");
		free(in);
		prompt(sh);
	}
	else if (*type == 1 && redi_ana(in, &bi, sh))
	{
		if (c == '<')
			err_print("new unexpected token `<`");
		else if (c == '>')
			err_print("new unexpected token `>`");
		free(in);
		prompt(sh);
	}
	*i = bi;
}
