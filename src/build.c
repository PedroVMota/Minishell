#include "minishell.h"





static t_cmds *setup(char **nodes)
{
	t_cmds *lst;
	int index;

	lst = NULL;
	index = 0;
	while(nodes[index])
	{
		lst = _add(nodes[index], &lst);
		if(nodes[index])
			free(nodes[index]);
		index++;
	}
	free(nodes);
	parse(lst);
	clean_commands(&lst);
	return lst;
}

t_cmds *ft_buildlst(char *elements)
{
	char **nodes;
	t_cmds *cmds;

	if (!elements)
		return NULL;
	switch_caracters(elements);
	nodes = ft_split(elements, TOKEN_PIPE);
	cmds = setup(nodes);
	return cmds;
}