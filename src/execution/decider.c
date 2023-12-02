/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:16:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/02 17:48:36 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_ptr_chooser(t_cmds *node)
{
	if (!node || !node->args)
		return ;
	if (!ft_strcmp(node->args[0], "echo"))
		node->ft_exec = &ft_echo;
	else if (!ft_strcmp(node->args[0], "cd"))
		node->ft_exec = &ft_cd;
	else if (!ft_strcmp(node->args[0], "pwd"))
		node->ft_exec = &ft_pwd;
	else if (!ft_strcmp(node->args[0], "export"))
		node->ft_exec = &ft_export;
	else if (!ft_strcmp(node->args[0], "unset"))
		node->ft_exec = &ft_unset;
	else if (!ft_strcmp(node->args[0], "env"))
		node->ft_exec = &ft_env;
	else if (!ft_strcmp(node->args[0], "exit"))
		node->ft_exec = &ft_exit;
	else
		node->ft_exec = &ft_exec;
}

void	pipeline(t_cmds *node)
{
	if (node->next)
	{
		if (pipe(node->pipe) == -1)
			perror("pipe");
		
	}
}

void	close_gen(t_cmds *head)
{
	if (head->pipe[1] != -1)
		close(head->pipe[1]);
	if (head->prev && head->prev->pipe[0] != -1)
		close(head->prev->pipe[0]);
	if (!head->next && head->pipe[0] != -1)
		close(head->pipe[0]);
}

void	create_pipe(t_cmds *cmd)
{
	if (cmd->prev)
    {
        dup2(cmd->prev->pipe[0], 0);
        close(cmd->prev->pipe[0]);
        close(cmd->prev->pipe[1]);
    }
    if (cmd->next)
    {
        dup2(cmd->pipe[1], 1);
        close(cmd->pipe[0]);
        close(cmd->pipe[1]);
    }
}

int	command_exe(t_cmds *cmd, int *ps, int *p)
{
    int	isfork;

    isfork = true;
    if (isbuiltin(cmd) && !(cmd->prev || cmd->next))
    {
        cmd->is_builtin = 1;
        isfork = false;
    }
    if (!isfork)
        cmd->ft_exec(cmd);
    else if ((isfork))
    {
        ps[*p] = fork();
        if (ps[*p] == 0)
        {
            free(ps);
			create_pipe(cmd);
            if (cmd->ft_exec)
                cmd->ft_exec(cmd);
            clean(cmd->sh, true, 1, "Child process failed");
        }
    }
    return (0);
}

int	software(t_shell *sh)
{
	int		*processlist;
	int		process;
	t_cmds	*head;
	int		status;

	process = 0;
	head = sh->cmds;
	processlist = ft_calloc(sh->lstsize, sizeof(int));
	if (!processlist)
		return (1);
	while (head)
	{
		pipeline(head); // check if there is a next if yes pipe.
		permission_tester(head);
		exec_ptr_chooser(head);
		command_exe(head, processlist, &process);
		close_gen(head);
		process++;
		status = head->sh->exit;
		head = head->next;
	}
	while (process > 0)
	{
		waitpid(processlist[--process], &status, 0);
		sh->exit = status >> 8;
	}
	free(processlist);
	return (0);
}
