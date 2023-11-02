/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:54 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/02 19:40:02 by pedromota        ###   ########.fr       */
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
		printf("i: %d\n", i);
		printf("Comparing %s and %s\n", temp->vars[0], new->vars[0]);
		if (strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			printf("Found repetition. Replacing value.\n");
			printf("Before replacement: %s\n", temp->vars[1]);
			if (temp->vars[1] == NULL)
				temp->vars[1] = (char *)malloc(ft_strlen(new->vars[1])
					* sizeof(char)); // Allocate memory for temp->vars[1]
			strcpy(temp->vars[1],
				new->vars[1]);                                       
				// Copy the contents of new->vars[1] to temp->vars[1]
			printf("After replacement: %s\n", temp->vars[1]);
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
	exit(0);
}

static  void	outfile(t_cmds *node)
{
	int	fd;

	fd = 1;
	if (node->next)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	if (dup2(fd, 1) == -1)
	{
		write(2, "Minishell: ", 12);
		perror("dup2");
		exit(1);
	}
	if (node->prev)
		close(node->prev->pipe[0]);
	if (node->pipe[0] != -1)
		close(node->pipe[0]);
	if (node->pipe[1] != -1)
		close(node->pipe[1]);
	if (node->redirection[0] != -1)
		close(node->redirection[0]);
	if (node->redirection[1] != -1)
		close(node->redirection[1]);
}

int	ft_export(t_cmds *node)
{
	int i = 1;
	t_env *new;
	outfile(node);

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
	exit(0);
	return (1);
}