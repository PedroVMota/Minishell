/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/10/24 00:28:13 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int standard_choiser(t_cmds *cmd)
{
    if (cmd->pipe[0] != -1)
        if (dup2(cmd->pipe[0], STDIN_FILENO) == -1)
            perror("dup2");
    if (cmd->redirection[0] != -1)
        if (dup2(cmd->redirection[0], STDIN_FILENO) == -1)
            perror("dup2");
    if (cmd->pipe[1] != -1 && cmd->redirection[1] == -1)
        if (dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
            perror("dup2");
    if (cmd->redirection[1] != -1)
        if (dup2(cmd->redirection[1], STDOUT_FILENO) == -1)
            perror("dup2");
    return 0;
}
