#include "minishell.h"

int	ft_exit(t_cmds *node)
{
	if (node->next)
		clean(node->sh, true, 0, NULL);
	return (0);
}
