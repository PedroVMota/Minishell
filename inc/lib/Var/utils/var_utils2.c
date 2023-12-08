/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:39:00 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/08 22:47:58 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vars.h"

char	*var_case_equal(t_env *vars, char *var, char *str);
char	*varlib_obtain(char *str);
char	*varlib_replace(char *str, char *new_value, char *del);
char	*varlib_delete_unknown(char *str);
void	update_quote(int *quote, char *s, int *index);

/// @brief This will search and replac or delete the string
/// @param str String Modified
/// @return the final string
char	*varlib_decide(char *str, t_shell *sh, int pos)
{
	t_env	*vars;
	char	*var;

	vars = sh->env;
	pos = varlib_start_position(str);
	var = NULL;
	if (pos == -1)
		return (str);
	while (vars)
	{
		var = varlib_obtain(str);
		if (!var)
			return (str);
		if (!ft_strcmp(var, vars->vars[0]))
			return (var_case_equal(vars, var, str));
		if (var[0] == '?')
			return (varlib_replace(str, ft_itoa(sh->exit), var));
		free(var);
		vars = vars->next;
	}
	return (varlib_delete_unknown(str));
}

char	*varlib_execute(char *s, t_shell *h)
{
	int	index;
	int	quote;

	quote = 0;
	index = 0;
	while (does_have_var(s))
	{
		update_quote(&quote, s, &index);
		if (s[index] == '$' && quote != 1)
		{
			s = varlib_decide(s, h, index);
			index = 0;
		}
		index++;
	}
	return (s);
}
