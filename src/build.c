/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:53:23 by pedro             #+#    #+#             */
/*   Updated: 2023/09/27 16:56:29 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmds	*setup(char **nodes)
{
	t_cmds	*lst;
	int		index;

	lst = NULL;
	index = 0;
	while (nodes[index])
	{
		lst = _add(nodes[index], &lst);
		if (nodes[index])
			free(nodes[index]);
		index++;
	}
	free(nodes);
	parse(lst);
	return (lst);
}

t_cmds	*ft_buildlst(char *elements)
{
	char	**nodes;
	t_cmds	*cmds;

	if (!elements)
		return (NULL);
	nodes = ft_split(elements, TOKEN_PIPE);
	cmds = setup(nodes);
	return (cmds);
}
