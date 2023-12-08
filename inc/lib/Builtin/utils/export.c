/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:02:42 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:29:21 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	print_export_env(t_cmds *node)
{
	t_env	*env;

	env = node->sh->env;
	while (env)
	{
		printf("declare -x ");
		print_export_char(env->vars[0], false);
		if (env->has_equal)
			printf("=\"");
		if (env->vars[1])
			print_export_char(env->vars[1], true);
		else if (!env->vars[1] && env->has_equal)
			printf("\"\n");
		else if (!env->vars[1] && !env->has_equal)
			printf("\n");
		env = env->next;
	}
	return ;
}

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
		if (node->args[*i][0] != '_'
			&& (node->args[*i][0] == '=' || !ft_isalpha(node->args[*i][0])))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				node->args[*i]);
			(*i)++;
			continue ;
		}
		if (ft_strchr(node->args[*i], '='))
			new = ft_env_add(ft_strdup(node->args[*i]), 1);
		else
			new = ft_env_add(ft_strdup(node->args[*i]), 0);
		check_repetition(new, &node->sh->env);
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
	if (node->next || node->prev)
		close_data(dups, node, true);
	else
		close_data(dups, node, false);
	return (1);
}
