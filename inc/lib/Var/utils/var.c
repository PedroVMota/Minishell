/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:11:12 by pedro             #+#    #+#             */
/*   Updated: 2023/11/21 22:21:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	varlib_start_position(char *ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		if (ptr[index] == QUOTE)
			return (-1);
		if (ptr[index] == '$' && ptr[index + 1] != '$')
			return (index);
		index++;
	}
	return (-1);
}

char	*varlib_obtain(char *str)
{
	char	*var;

	int start, end;
	start = varlib_start_position(str) + 1;
	end = start;
	if (start == -1)
		return (NULL);
	if (str[start] == '?')
		return (ft_strdup("?"));
	while (str[end] && !(str[end] == ' ' || str[end] == '$'
			|| !ft_isalnum(str[end])))
		end++;
	var = ft_substr(str, start, end - start);
	return (var);
}

char	*varlib_replace(char **str, char *new_value, char *del)
{
	int		flag;
	char	*result;
	char	*p;
	char	*q;

	printf("%s Function is being called with sucess %s\n", HBLU, RESET);
	printf("%sString%s: %s\n", HBLU, RESET, *str);
	printf("%sNew Value%s: %s\n", HBLU, RESET, new_value);
	flag = 0;
	result = malloc(ft_strlen(*str) + ft_strlen(new_value) + 1);
	p = *str;
	q = result;
	flag = 0;
	if (result == NULL)
	{
		if (del)
			free(del);
		return (*str);
	}
	while (*p != '\0')
	{
		if (*p == '$' && flag == 0)
		{
			if (ft_strncmp(p + 1, del, ft_strlen(del)) == 0)
			{
				ft_strlcpy(q, new_value, ft_strlen(new_value) + 1);
				q += ft_strlen(new_value);
				p += ft_strlen(del) + 1;
			}
			flag = 1;
		}
		else
			*q++ = *p++;
	}
	*q = '\0';
	free(del);
	free(new_value);
	return (result);
}

char	*varlib_delete_unknown(char *str)
{
	char	*result;
	char	*p;
	char	*q;

	result = malloc(ft_strlen(str) + 1);
	p = str;
	q = result;
	if (result == NULL)
		return (str);
	while (*p != '\0')
	{
		if (*p == '$')
			while (*p != QUOTE && *p != ' ' && *p + 1 != '$' && *p != '\0')
				p++;
		else
			*q++ = *p++;
	}
	*q = '\0';
	free(str);
	return (result);
}

/// @brief This will search and replac or delete the string
/// @param str String Modified
/// @return the final string
char	*varlib_decide(char *str, t_shell *sh, int position)
{
	int		pos;
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
		printf("First Char %c\n", var[0]);
		if (!ft_strcmp(var, vars->vars[0]))
			return (varlib_replace(&str, ft_strdup(vars->vars[1]), var));
		if (var[0] == '?')
			return (varlib_replace(&str, ft_itoa(sh->exit), var));
		free(var);
		vars = vars->next;
	}
	return (varlib_delete_unknown(str));
}

char	*varlib_execute(char *s, t_shell *h)
{
	int index;
	char quote;

	index = 0;
	quote = 0;
	if (!s)
		return (s);
	while (s[index] && index < strlen(s))
	{
		if (s[index] == '\'' && quote == 0)
			quote = s[index];
		else if (s[index] == '\'' && quote != 0)
			quote = 0;
		else if (s[index] == '$' && !quote)
			s = varlib_decide(s, h, index);
		index++;
	}
	return (s);
}