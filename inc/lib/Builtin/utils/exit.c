/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:03 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 22:27:37 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	close_data(int *dups)
{
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	free(dups);
}

long long	count_args(char **s)
{
	long long	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*check_first(char **s)
{
	int	i;

	i = -1;
	while (s[0][++i])
	{
		if ((s[0][i] < '0' && s[0][i] > '9'))
		{
			printf("I: %d\n", i);
			return ("NUMERIC_ERROR_ERR_2");
		}
	}
	if (count_args(s) > 2)
		return ("TOO_MANY_ARGUMENTS_NOT_CLOSE");
	return ("OK");
}

int	ft_exit(t_cmds *node)
{
	char	*security;
	int		*dups;

	security = check_first(node->args);
	redirect(node);
	dups = set_dups(node);
	if (!(node->prev || node->next))
		write(1, "exit\n", 6);
	if (ft_strcmp(security, "NUMERIC_ERROR_ERR_2") == 0)
	{
		close_data(dups);
		clean(node->sh, true, 2, "exit: numeric argument required\n");
	}
	else if (ft_strcmp(security, "TOO_MANY_ARGUMENTS_NOT_CLOSE") == 0)
	{
		close_data(dups);
		write(2, "exit: too many arguments\n", 2);
	}
	else if (ft_strcmp(security, "OK") == 0)
	{
		close_data(dups);
		clean(node->sh, true, ft_atoi(node->args[1]), NULL);
	}
	return (0);
}
