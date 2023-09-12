#include <minishell.h>

bool CheckValid(char *ptr)
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