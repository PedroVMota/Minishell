/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/25 19:05:22 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_in(t_cmds *node)
{
    int	fd;

    fd = -1;
    if (node->prev)
        fd = node->prev->pipe[0];
    if (node->redirection[0] != -1)
        fd = node->redirection[0];
    return (fd);
}

static int	get_ou(t_cmds *node)
{
    int	fd;

    fd = -1;
    if (node->prev)
        fd = node->prev->pipe[1];
    if (node->next)
        fd = node->pipe[1];
    if (node->redirection[1] != -1)
        fd = node->redirection[1];
    if (!node->next && node->redirection[1] == -1) // Add this check
        fd = STDOUT_FILENO;
    return (fd);
}

static void	end_endpoits(t_cmds *cmd)
{
    if (cmd->prev)
        close(cmd->prev->pipe[0]);
    if (cmd->pipe[0] != -1)
        close(cmd->pipe[0]);
    if (cmd->pipe[1] != -1)
        close(cmd->pipe[1]);
    if (cmd->redirection[0] != -1)
        close(cmd->redirection[0]);
    if (cmd->redirection[1] != -1)
        close(cmd->redirection[1]);
}

int	standard_choiser(t_cmds *cmd)
{
    int	fdi;
    int	fdo;

    fdi = get_in(cmd);
    fdo = get_ou(cmd);
    if (fdi == -1 || fdo == -1)
    {
        end_endpoits(cmd);
        return (0);
    }
    if (dup2(fdi, STDIN_FILENO) == -1)
    {
        write(2, "Minishell: ", 11);
        perror("Input Dup");
        return (1);
    }
    if (dup2(fdo, STDOUT_FILENO) == -1)
    {
        write(2, "Minishell: ", 11);
        perror("Output Dup");
        return (1);
    }
    end_endpoits(cmd);
    return (0);
}
