/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:02:42 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 01:06:23 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	swpnodes(t_env *a, t_env *b);
void	print_export_char(char *str, bool _print_new_line);

int	check_repetition(t_env *new, t_env **env)
{
	t_env	*temp;
	int		i;

	temp = *env;
	i = 0;
	if (new->vars[0][0] == '=')
	{
		printf("minishell: %s is not a valid identifier\n", new->vars[0]);
		return (1);
	}
	while (temp)
	{
		if (ft_strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			if (temp->vars[1] == NULL)
				temp->vars[1] = (char *)malloc(ft_strlen(new->vars[1])
					* sizeof(char));
			ft_strlcpy(temp->vars[1], new->vars[1], strlen(temp->vars[1]));
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

void	print_export_env(t_cmds *node)
{
	t_env	*env;

	env = node->sh->env;
	while (env)
	{
		printf("declare -x ");
		print_export_char(env->vars[0], false);
		if (env->vars[1])
		{
			printf("=\"");
			print_export_char(env->vars[1], true);
		}
		env = env->next;
	}
	return ;
}



void	list_order(t_env *node)
{
	int		sw;
	t_env	*prf;
	t_env	*prs;

	sw = 1;
	while (sw)
	{
		sw = 0;
		prf = node;
		prs = NULL;
		while (prf->next != prs)
		{
			if (ft_strcmp(prf->vars[0], prf->next->vars[0]) > 0)
			{
				swpnodes(prf, prf->next);
				sw = 1;
			}
			prf = prf->next;
		}
		prs = prf;
	}
}

int	ft_export(t_cmds *node)
{
	t_env	*new;
	int		*dups;
	int		i;

	dups = NULL;
	i = 1;
	redirect(node);
	dups = set_dups(node);
	if (!node->args[i])
	{
		print_export_env(node);
		if (dups[0] != -10)
			close(dups[0]);
		if (dups[1] != -10)
			close(dups[1]);
		close_redi(node);
		free(dups);
		return (1);
	}
	while (node->args[i])
	{
		new = ft_env_add(ft_strdup(node->args[i]));
		if (check_repetition(new, &node->sh->env) == 0)
			ft_ml_envadd_back(&node->sh->env, new);
		else
			ft_env_delete(&new);
		i++;
	}
	list_order(node->sh->env);
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	if (node->next || node->prev)
	{
		close_redi(node);
		free(dups);
		clean(node->sh, true, 0, NULL);
	}
	close_redi(node);
	free(dups);
	return (1);
}