/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:12:23 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 18:16:35 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

static void	close_data(int *dups, t_cmds *node, bool exit)
{
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	close_redi(node);
	free(dups);
	if (exit)
		clean(node->sh, true, 0, NULL);
}

void	remove_node(t_env **head, char *content)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *head;
	(void)content;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		if (current && current->vars && !ft_strcmp(current->vars[0], content))
			break ;
	}
	if (current != NULL)
	{
		if (previous != NULL)
			previous->next = current->next;
		else
			*head = current->next;
		free_split(current->vars, 0);
		free(current);
	}
}

int	check_invalid(t_cmds *node, char *arg, int word)
{
	int	i;

	i = 0;
	if (arg[i] >= 48 && arg[i] <= 57)
	{
		write(1, "Minishell: unset: `", 20);
		write(1, arg, ft_strlen(arg));
		write(1, "': not a valid identifier\n", 27);
		return (1);
	}
	while (arg[i])
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
		{
			write(1, "Minishell: unset: `", 20);
			write(1, arg, ft_strlen(arg));
			write(1, "': not a valid identifier\n", 27);
			return (1);
		}
		i++;
	}
	if (ft_strlen(node->args[word]) != ft_strlen(arg))
		return (1);
	return (0);
}

int	ft_unset(t_cmds *node)
{
	int	i;
	int	*dups;
	int	err;

	i = 0;
	err = 0;
	redirect(node);
	dups = set_dups(node);
	if (!dups)
		NULL;
	if (!node->args[i])
	{
		close_data(dups, node, false);
		return (1);
	}
	while (node->args[++i])
		if (!check_invalid(node, node->args[i], i))
			remove_node(&node->sh->env, node->args[i]);
	if (node->next || node->prev)
		close_data(dups, node, true);
	else
		close_data(dups, node, false);
	return (1);
}
