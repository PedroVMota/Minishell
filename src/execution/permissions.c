/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:36:02 by pedro             #+#    #+#             */
/*   Updated: 2023/11/29 14:36:08 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	f_perm(char *name, char **paths)
{
	if (access(name, F_OK) == 0)
	{
		free_split(paths, 0);
		return (true);
	}
	return (false);
}
