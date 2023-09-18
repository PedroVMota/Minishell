#include "minishell.h"





static t_cmds *setup(char **nodes)
{
	t_cmds *lst;
	int index;

	lst = NULL;
	index = -1;
	while(nodes[++index])
	{
		lst = _add(nodes[index], &lst);
	}
	return lst;
}

t_cmds *ft_buildlst(char *elements)
{
	char **nodes;
	int index = 0;
	t_cmds *cmds;

	if (!elements)
		return NULL;
	switch_caracters(elements);
	nodes = ft_split(elements, TOKEN_PIPE);
	cmds = setup(nodes);
	CommandDisplay(cmds);
	free_split(nodes);
	return cmds;
}