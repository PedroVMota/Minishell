/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Runner.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:44:15 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 23:06:39 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_detector(t_cmds *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (true);
	return (false);
}

void	exec_ptr_chooser(t_cmds *node)
{
	if (!node)
		return ;
	if (!node->args || !node->args[0])
		node->ft_exec = &ft_exec;
	else if (!ft_strcmp(node->args[0], "echo"))
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

void	wait_for_child(t_shell *sh, int **processlist, int *process)
{
	int		status;
	t_cmds	*head;

	head = sh->cmds;
	while (*processlist && *process > 0)
	{
		if (head != NULL && isbuiltin(head) && !(head->prev || head->next))
		{
			head = head->next;
			(*process)--;
			continue ;
		}
		waitpid((*processlist)[--(*process)], &status, 0);
		head = head->next;
		sh->exit = status >> 8;
	}
	if (*processlist)
		free(*processlist);
}

void	run_parrent(t_cmds *node, int **ps)
{
	if (node->ft_exec == &ft_exit)
	{
		free(*ps);
		ps = NULL;
	}
	node->ft_exec(node);
}

void	wait_case_heredoc(t_shell *sh, t_cmds *cmd, int **ps, int *p)
{
	int	check_error;

	check_error = 0;
	ft_ml_sigdefault(SIG_STATE_IGNORE);
	if (cmd->args && t_redirection_has_hd(cmd->infiles)
		&& !ft_strcmp(cmd->args[0], "./minishell"))
		waitpid(*ps[*p], &check_error, 0);
	ft_ml_sigdefault(SIG_STATE_PARENT);
	if (check_error >> 8 == 130)
	{
		g_signal_status = SIGNAL_EXIT_HD;
		sh->stop = 1;
	}
}

//t_redirection_has_hd(cmd->infiles) 