#include "minishell.h"

void	remove_node(t_env **head, char *content)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *head;
	while (current->next != NULL && ft_strcmp(current->vars[0], content))
	{
		previous = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (previous != NULL)
			previous->next = current->next;
		else
			*head = current->next;
		free(current);
	}
}

int	ft_unset(t_cmds *node)
{
	int	i;

	i = 0;
	redirect(node);
	if (!node->args[i])
	{
		close_redi(node);
		return (1);
	}
	while (node->args[++i])
		remove_node(&node->sh->env, node->args[i]);
	close_redi(node);
	return (1);
}
