#include "minishell.h"

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int	ft_env(t_cmds *node)
{
	t_env *env = node->sh->env;
	standard_choiser(node);
	while (env)
	{
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	exit(0);
	return (0);
}