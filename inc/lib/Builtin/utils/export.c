/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:54 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/01 16:26:42 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			if (temp->vars[1] == NULL)
				temp->vars[1]
					= (char *)malloc(ft_strlen(new->vars[1]) * sizeof(char));
			strcpy(temp->vars[1], new->vars[1]);
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
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	return ;
}

void	list_order(t_cmds *node)
{
	t_env	*temp;
	t_env	*temp2;
	char	*aux;

	temp = node->sh->env;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (strcmp(temp->vars[0], temp2->vars[0]) > 0)
			{
				aux = temp->vars[0];
				temp->vars[0] = temp2->vars[0];
				temp2->vars[0] = aux;
				aux = temp->vars[1];
				temp->vars[1] = temp2->vars[1];
				temp2->vars[1] = aux;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

int	ft_export(t_cmds *node)
{
	int		i;
	t_env	*new;

	i = 1;
	if (!node->args[i])
	{
		print_export_env(node);
		return (1);
	}
	while (node->args[i])
	{
		new = ft_env_add(ft_strdup(node->args[i]));
		if (check_repetition(new, &node->sh->env) == 0)
		{
			printf("\nno reps\n");
			ft_ml_envadd_back(&node->sh->env, new);
		}
		i++;
	}
	list_order(node);
	return (1);
}