/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 04:57:07 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 22:48:31 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vars.h"

bool	does_have_var(char *s);
void	skip_single_quote(char *s, int *index, int *quote);
void	update_quote(int *quote, char *s, int *index);
void	fill_result(char *result, char *new_value, char *del, size_t **m);

char	*varlib_obtain(char *str)
{
	char	*var;
	int		start;
	int		end;

	start = varlib_start_position(str) + 1;
	end = start;
	if (start == -1)
		return (NULL);
	if (str[start] == '?')
		return (ft_strdup("?"));
	while (str[end] && !(str[end] == ' ' || str[end] == '$'))
	{
		if (!ft_isalnum(str[end]) && str[end] == '_')
			end++;
		if (!ft_isalnum(str[end]))
			break ;
		end++;
	}
	var = ft_substr(str, start, end - start);
	return (var);
}

char	*varlib_replace(char *str, char *new_value, char *del)
{
	char	*result;
	size_t	i;
	size_t	j;
	int		quote;

	quote = 0;
	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str) - ft_strlen(del) 
			+ ft_strlen(new_value) + 1);
	if (!result)
		return (free_array((char *[]){str, new_value, del, NULL}));
	while (i < ft_strlen(str))
	{
		update_quote(&quote, str, (int *)&i);
		if (str[i] == '$' && ft_strncmp(str + i + 1, del, ft_strlen(del)) == 0
			&& quote != 1)
			fill_result(result, new_value, del, (size_t *[2]){&i, &j});
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free_array((char *[]){str, new_value, del, NULL});
	return (result);
}

static bool	skip(char *str, int *end)
{
	if (!ft_isalnum(str[*end]) && str[*end] == '_')
		(*end)++;
	if (!ft_isalnum(str[*end]))
		return (true);
	return (false);
}

char	*varlib_delete_unknown(char *str)
{
	size_t	len;
	size_t	newlen;
	int		start;
	int		end;
	char	*result;

	len = ft_strlen(str);
	start = varlib_start_position(str);
	end = start + 1;
	while (str[end] && !(str[end] == ' ' || str[end] == '$'))
	{
		if (skip(str, &end))
			break ;
		end++;
	}
	newlen = len - (end - start);
	if (newlen == 0)
		return (trash((char *[]){str, NULL}));
	result = (char *)malloc(newlen + 1);
	if (!result)
		return (str);
	ft_strlcpy(result, str, start + 1);
	ft_strlcpy(result + start, str + end, len - end + 1);
	free(str);
	return (result);
}

char	*var_case_equal(t_env *vars, char *var, char *str)
{
	if (vars->has_equal)
		return (varlib_replace(str, ft_strdup(vars->vars[1]), var));
	return (varlib_delete_unknown(str));
}
