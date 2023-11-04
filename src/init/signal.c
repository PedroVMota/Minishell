/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:54:48 by pedro             #+#    #+#             */
/*   Updated: 2023/11/04 10:24:03 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ml_sigdefault(void)
{
	signal(SIGINT, (void *)handle_sign);
	signal(SIGQUIT, (void *)handle_quit);
}

void	handle_quit(int sig, t_shell *sh)
{
	pid_t			id;
	static t_shell	*center;
	int				status;

	(void)sig;
	if (!center)
	{
		center = sh;
		return ;
	}
	id = waitpid(-1, &status, 0);
	if (id == -1)
		(void)(SIG_IGN);
}

void	handle_sign(int sig, t_shell *sh)
{
	pid_t			pid;
	static t_shell	*center;
	int				status;

	(void)sig;
	if (!center)
	{
		center = sh;
		return ;
	}
	pid = waitpid(-1, &status, 0);
	write(2, "^C", 2);
	write(2, "\n", 1);
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
