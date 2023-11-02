/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:54:48 by pedro             #+#    #+#             */
/*   Updated: 2023/11/02 22:37:52 by pedromota        ###   ########.fr       */
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
	pid_t id;
    int status;
	static t_shell *fodase;

    (void)sig;
    id = waitpid(-1, &status, 0);
	if (!fodase)
	{
		fodase = sh;
		return ;
	}
    if (id == -1)
        SIG_IGN;
    else if(!fodase->hd)
    {
        write(1, "Quit (core dumped)\n", 20);
        return;
    }
}

void	handle_sign(int sig, t_shell *sh)
{
	pid_t			pid;
	static t_shell	*fodase;
	int				status;

	(void)sig;
	pid = waitpid(-1, &status, 0);
	if (!fodase)
	{
		fodase = sh;
		return ;
	}
	write(2, "^C\n", 3);
	if (sh->hd)
	{
		sh->stop = 1;
		return ;
	}
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
