#include "minishell.h"

void	ft_ml_sigdefault(void)
{
	signal(SIGINT, (void *)handle_sign);
	signal(SIGQUIT, SIG_IGN);
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
	{
		printf("\b \b");
	}

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
	write(2, "\n", 1);
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
