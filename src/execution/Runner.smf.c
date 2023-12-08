/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Runner.smf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:07:18 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 21:17:34 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process_signal_updater(t_cmds *cmd)
{
	if (isbuiltin(cmd))
		ft_ml_sigdefault(SIG_STATE_CHILD_BUILTIN);
	else
		ft_ml_sigdefault(SIG_STATE_CHILD);
}

void	execute_command(t_cmds *cmd, int *isfork, int **ps, int *p)
{
	if (!*isfork)
	{
		ft_ml_sigdefault(SIG_STATE_PARENT);
		run_parrent(cmd, ps);
	}
	else if ((*isfork))
	{
		ft_ml_sigdefault(SIG_STATE_PARENT);
		(*ps)[*p] = fork();
		if ((*ps)[*p] == 0)
		{
			child_process_signal_updater(cmd);
			free((*ps));
			cmd->ft_exec(cmd);
			clean(cmd->sh, true, 0, NULL);
		}
		else
			wait_case_heredoc(cmd->sh, cmd, ps, p);
	}
}
