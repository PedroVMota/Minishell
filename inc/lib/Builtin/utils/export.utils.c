/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:04:25 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 05:43:12 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	swpnodes(t_env *a, t_env *b)
{
	char	**temp;

	temp = a->vars;
	a->vars = b->vars;
	b->vars = temp;
}

void	print_export_char(char *str, bool _print_new_line)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return ;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			printf("\\n");
			if (str[i + 1] != '\0')
				i++;
		}
		else
			printf("%c", str[i]);
		i++;
	}
	if (_print_new_line)
		printf("\"\n");
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
			if (env->has_equal)
				printf("=\"");
			print_export_char(env->vars[1], true);
		}
		else
			printf("\n");
		env = env->next;
	}
	return ;
}

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
