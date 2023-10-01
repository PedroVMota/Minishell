/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:54:48 by pedro             #+#    #+#             */
/*   Updated: 2023/09/23 10:22:21 by pedro            ###   ########.fr       */
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
	else if (!g_shell.hd)
	{
		write(1, "Quit (core dumped)\n", 20);
		return ;
	}
}

void	handle_sign(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, 0);
	g_shell.exit = 130;
	write(2, "^C", 2);
	write(2, "\n", 1);
	if (g_shell.hd)
	{
		g_shell.stop = 1;
		return ;
	}
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
