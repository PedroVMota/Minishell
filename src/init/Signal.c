/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:52:55 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 13:35:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_print(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

static void	sh_main(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_status = SIGNAL_NEW_LINE;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sh_hd(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		g_signal_status = SIGNAL_EXIT_HD;
	}
}

void	ft_ml_sigdefault_keep(int sig_state)
{
	if (sig_state == SIG_STATE_CHILD_BUILTIN)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_HD_CHILD)
	{
		signal(SIGINT, sh_hd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_ml_sigdefault(int sig_state)
{
	if (sig_state == SIG_STATE_MAIN)
	{
		signal(SIGINT, sh_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_state == SIG_STATE_PARENT)
	{
		signal(SIGINT, sh_print);
		signal(SIGQUIT, sh_print);
	}
	else
		ft_ml_sigdefault_keep(sig_state);
}
