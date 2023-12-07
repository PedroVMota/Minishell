/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Runner.smf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:07:18 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 21:31:09 by pedro            ###   ########.fr       */
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