#include "minishell.h"
#include "vars.h"

bool	does_have_var(char *s);

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
	while (str[end] && !(str[end] == ' ' || str[end] == '$'
			|| !ft_isalnum(str[end])))
		end++;
	var = ft_substr(str, start, end - start);
	return (var);
}

char	*varlib_replace(char *str, char *new_value, char *del)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str) - ft_strlen(del)
			+ ft_strlen(new_value) + 1);
	if (!result)
		return (free_array((char *[]){str, new_value, del, NULL}));
	while (i < ft_strlen(str))
	{
		if (str[i] == '$' && strncmp(str + i + 1, del, ft_strlen(del)) == 0)
		{
			strcpy(result + j, new_value);
			j += ft_strlen(new_value);
			i += ft_strlen(del) + 1;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free_array((char *[]){str, new_value, del, NULL});
	return (result);
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
	while (str[end] && !(str[end] == ' ' || str[end] == '$'
			|| !ft_isalnum(str[end])))
		end++;
	newlen = len - (end - start);
	if (newlen == 0)
		return trash((char *[]){str, NULL});
	result = (char *)malloc(newlen + 1);
	if (!result)
		return (str);
	ft_strlcpy(result, str, start + 1);
	ft_strlcpy(result + start, str + end, len - end + 1);
	free(str);
	return (result);
}

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
			return (varlib_replace(str, ft_strdup(vars->vars[1]), var));
		if (var[0] == '?')
			return (varlib_replace(str, ft_itoa(sh->exit), var));
		free(var);
		vars = vars->next;
	}
	return (varlib_delete_unknown(str));
}

char	*varlib_execute(char *s, t_shell *h)
{
	int		index;
	char	quote;

	index = 0;
	quote = 0;
	while (does_have_var(s))
	{
		if (s[index] == '\'' && quote == 0)
			quote = s[index];
		else if (s[index] == '\'' && quote != 0)
			quote = 0;
		else if (s[index] == '$' && !quote)
		{
			s = varlib_decide(s, h, index);
			index = 0;
		}
		index++;
	}
	return (s);
}
