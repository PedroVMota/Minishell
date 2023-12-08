/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:04:25 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:21:43 by oharoon          ###   ########.fr       */
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

static void	env_replace(t_env *temp, t_env *new)
{
	char	**olds;

	temp->has_equal = new->has_equal;
	olds = temp->vars;
	temp->vars = new->vars;
	free_split(olds, 0);
	new->vars = NULL;
	ft_env_delete(&new);
}

int	check_repetition(t_env *new, t_env **env)
{
	t_env	*temp;
	int		i;

	temp = *env;
	i = 0;
	while (temp)
	{
		if (ft_strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			env_replace(temp, new);
			return (0);
		}
		temp = temp->next;
		i++;
	}
	ft_ml_envadd_back(env, new);
	return (0);
}
