/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:02:42 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/07 01:01:38 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void		list_order(t_env *node);
void		swpnodes(t_env *a, t_env *b);
void		print_export_char(char *str, bool _print_new_line);
void		print_export_env(t_cmds *node);
int			check_repetition(t_env *new, t_env **env);

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

static int	just_print(t_cmds *node, int *i, int *dups)
{
	if (!node->args[*i])
	{
		print_export_env(node);
		close_data(dups, node, false);
		return (0);
	}
	return (1);
}

static void	add_to_the_list(t_cmds *node, int *i)
{
	t_env	*new;

	new = NULL;
	while (node->args[*i])
	{
		if (ft_strchr(node->args[*i], '='))
			new = ft_env_add(ft_strdup(node->args[*i]), 1);
		else
			new = ft_env_add(ft_strdup(node->args[*i]), 0);
		if (check_repetition(new, &node->sh->env) == 0)
			ft_ml_envadd_back(&node->sh->env, new);
		else
			ft_env_delete(&new);
		(*i)++;
	}
}

int	ft_export(t_cmds *node)
{
	int	i;
	int	*dups;

	dups = NULL;
	i = 1;
	redirect(node);
	dups = set_dups(node);
	if (just_print(node, &i, dups) == 0)
		return (0);
	else
		add_to_the_list(node, &i);
	list_order(node->sh->env);
	if(node->next || node->prev)
		close_data(dups, node, true);
	else
		close_data(dups, node, false);
	return (1);
}
