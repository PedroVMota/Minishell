/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:57:02 by oharoon           #+#    #+#             */
/*   Updated: 2023/12/06 01:00:10 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

int	check_all_paths(t_cmds *head, int *err, int *type);

int	permission_tester(t_cmds *head, int arr[])
{
	int	type;

	type = 1;
	arr[0] = 0;
	arr[1] = 0;
	check_all_paths(head, &head->sh->exit, &type);
	if (head->sh->exit != 0 && type == 1)
	{
		arr[0] = head->sh->exit;
		arr[1] = type;
		return (true);
	}
	else if (head->sh->exit != 0 && type == 2)
	{
		arr[0] = head->sh->exit;
		arr[1] = type;
		return (true);
	}
	else if (head->sh->exit == 126)
	{
		arr[0] = head->sh->exit;
		arr[1] = type;
		return (true);
	}
	return (false);
}
