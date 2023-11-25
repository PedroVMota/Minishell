/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:54:48 by pedro             #+#    #+#             */
/*   Updated: 2023/11/25 16:35:07 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_ml_sigdefault(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

void	handle_quit(int sig)
{
	pid_t	id;
	int		status;

	(void)sig;
	id = waitpid(-1, &status, 0);
	if (id == -1)
		(void)(SIG_IGN);
}

void	handle_sign(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, 0);
	// write(2, "^C", 2);
	// write(2, "\n", 1);
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
