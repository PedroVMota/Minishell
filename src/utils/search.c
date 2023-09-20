#include <minishell.h>

int var_index_simbol(char *ptr)
{
	int index;

	index = 0;
	if (!ptr)
		return 0;
	while (ptr[index])
	{
		if (ptr[index] == TOKEN_QUOTE)
			return -1;
		if (ptr[index] == '$')
			return index;
		index++;
	}
	return -1;
}

/// @brief Replace the content.
/// @param str The first position of the str
/// @param new_value the new content
/// @param del Is gonna be the content that will be replaced;
/// @return Return the head position of the lsit
static char *replace(char *str, char *new_value, char *del)
{

	MEMDEBUG(__func__, NULL);
	char *result = malloc(strlen(str) + 1);
	char *p = str;
	char *q = result;
	if (result == NULL)
		return str;
	while (*p != '\0')
	{
		if (*p == '$')
		{
			if (ft_strncmp(p + 1, del, strlen(del)) == 0)
			{
				ft_strlcpy(q, new_value, ft_strlen(new_value) + 1);
				q += ft_strlen(new_value);
				p += ft_strlen(del) + 1;
			}
		}
		else
			*q++ = *p++;
	}
	*q = '\0';
	free(str);
	return result;
}

/// @brief Replace the content.
/// @param str The content
/// @return without the variable name
static char *delete(char *str)
{

	MEMDEBUG(__func__, __func__);
	char *result = malloc(strlen(str) + 1);
	char *p = str;
	char *q = result;
	if (result == NULL)
		return str;
	while (*p != '\0')
	{
		if (*p == '$')
			while (*p != TOKEN_DQUOTE && *p != '\0')
				p++;
		else
			*q++ = *p++;
	}
	*q = '\0';
	free(str);
	return result;
}

char *VarCheckValid(char *ptr)
{
	t_env *vars;
	char *var;

	var = NULL;
	vars = g_shell.env;
	int index = var_index_simbol(ptr);
	while (vars)
	{
		var = ft_substr(&ptr[index + 1], 0, ft_strlen(vars->vars[0]));
		if (!var)
			return false;
		if (!ft_strcmp(var, vars->vars[0]))
		{
			return replace(ptr, vars->vars[1], var);
		}
		free(var);
		vars = vars->next;
	}
	return delete (ptr);
}

bool var_state(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (str[index] == TOKEN_QUOTE)
			return false;
		if (str[index] == '$')
			return true;
		index++;
	}
	return false;
}

void var_replacer(char **str)
{
	int var_pos;

	if (!*str)
		return;
	if (!var_state(*str))
		return;
	var_pos = var_index_simbol(*str);
	if (var_pos == -1)
		return;
	*str = VarCheckValid(*str);
}