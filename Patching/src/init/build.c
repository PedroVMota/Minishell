#include "minishell.h"

int	cmd_size(t_cmds *head)
{
	int	size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

static t_cmds	*setup(char **nodes, t_shell *sh)
{
	t_cmds	*lst;
	int		index;

	lst = NULL;
	index = 0;
	sh->lstsize = 0;
	while (nodes[index])
	{
		lst = _add(nodes[index], &lst, sh);
		if (nodes[index])
			free(nodes[index]);
		index++;
	}
	sh->lstsize = cmd_size(lst);
	free(nodes);
	parse(lst, sh);
	return (lst);
}

t_cmds	*ft_buildlst(char *elements, t_shell *sh)
{
	char	**nodes;
	t_cmds	*cmds;

	if (!elements)
		return (NULL);
	nodes = ft_split(elements, PIPE);
	if (!nodes)
		return (NULL);
	cmds = setup(nodes, sh);
	cmds->is_builtin = 0;
	cmds->saved_stdin = -1;
    cmds->saved_stdout = -1;
	free(elements);
	return (cmds);
}
