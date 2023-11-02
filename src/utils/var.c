/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:11:12 by pedro             #+#    #+#             */
/*   Updated: 2023/11/02 21:24:29 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_variable(char *str)
{
	char	*var;

	int start, end;
	start = var_pos(str) + 1;
	end = start;
	if (start == -1)
		return (NULL);
	while (str[end] && !(str[end] == ' ' || str[end] == '$'))
		end++;
	var = ft_substr(str, start, end - start);
	return (var);
}

char	*replace_var(char *str, char *new_value, char *del)
{
	int		flag;
	char	*result;
	char	*p;
	char	*q;

	flag = 0;
	result = malloc(ft_strlen(str) + ft_strlen(new_value) + 1);
	p = str;
	q = result;
	flag = 0;
	if (result == NULL)
	{
		if (del)
			free(del);
		return (str);
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
	free(str);
	free(del);
	return (result);
}

char *delete(char *str)
{
	char *result;
	char *p;
	char *q;


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