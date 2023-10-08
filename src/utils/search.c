/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:08:35 by pedro             #+#    #+#             */
/*   Updated: 2023/09/25 12:16:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE || str[i] == QUOTE)
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

/// @brief Check position index of the variable
/// @param ptr string that will be searched
/// @return return a integer if exit otherwise -1
int	var_pos(char *ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		if (ptr[index] == QUOTE)
			return (-1);
		if (ptr[index] == '$')
			return (index);
		index++;
	}
	return (-1);
}

/// @brief Check if the There is a variable simbol in the string
/// @param str the string that will be checked
/// @return true or false depending if does exist a $ inside
bool	check_variable(char *str)
{
	int	second_layer;

	second_layer = 0;
	while (str[second_layer])
	{
		if (str[second_layer] == QUOTE)
			return (false);
		if (str[second_layer] == '$' && str[second_layer + 1] != 0)
			return (true);
		second_layer++;
	}
	return (false);
}

/// @brief This will search and replac or delete the string
/// @param str String Modified
/// @return the final string
char	*manage(char *str)
{
	int		pos;
	t_env	*vars;
	char	*var;

	vars = g_shell.env;
	pos = var_pos(str);
	var = NULL;
	if (pos == -1)
		return (str);
	while (vars)
	{
		var = ft_substr(&str[pos + 1], 0, ft_strlen(vars->vars[0]));
		if (!ft_strcmp(var, vars->vars[0]))
			return (replace_var(str, vars->vars[1], var));
		free(var);
		vars = vars->next;
	}
	return (delete (str));
}

char	*varcheckvalid(char *ptr)
{
	char	*final;

	final = 0;
	if (!check_variable(ptr) || !ptr)
		return (ptr);
	else
	{
		final = manage(ptr);
		return (final);
	}
	return (ptr);
}

int	variable_counter(char *str)
{
	int	second_layer;
	int	counter;

	counter = 0;
	second_layer = 0;
	while (str[second_layer])
	{
		if (str[second_layer] == QUOTE)
			return (-1);
		if (str[second_layer] == '$')
			counter++;
		second_layer++;
	}
	return (counter);
}
