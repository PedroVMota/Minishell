/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:11:33 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/28 15:12:38 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmds *node)
{
	(void)node;
	char path[1024]; // Allocate space for the path

    if (getcwd(path, sizeof(path)) != NULL) {
        printf("%s\n", path); // Print the current working directory
    } else {
        perror("getcwd() error");
        return 1;
    }
    exit(0);
	return (0);
}