#include <minishell.h>

bool VarCheckValid(char *ptr)
{
	t_env *vars;
	char *var;

	var = NULL;
	vars = g_shell.env;
	while(vars)
	{
		var = ft_substr(ptr + 1, 0, vars->var_len);
		if(!var)
			return false;
		if(!ft_strcmp(var, vars->var))
			return true;
		vars = vars->next;
	}
}

t_counter VarCounter(char *ptr)
{
	t_counter count;
	t_mode ar;

	ar = ENV_MODE_TOKEN; // old 
	count = 0;
	if(!ptr)
		return 0;
	while(ptr && *ptr)
	{
		ft_mode_changer_ascii(*ptr, &ar);
		if(*ptr == '$' && (ar != ENV_MODE_QUOTE) && VarCheckValid(ptr))
			count++;
		ptr++;
	}
	return count;
}
