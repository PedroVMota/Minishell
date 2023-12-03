/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:54 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/03 13:54:45 by pedro            ###   ########.fr       */
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
		if (ft_strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			if (temp->vars[1] == NULL)
				temp->vars[1]
					= (char *)malloc(ft_strlen(new->vars[1]) * sizeof(char));
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
	redirect(node);
	if (!node->args[i])
	{
		print_export_env(node);
		close_redi(node);
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
	list_order(node);
	if(node->next || node->prev)
		clean(node->sh, true, 0, NULL);
	return (1);
}