/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:53:03 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 18:12:16 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_status;

bool	isallwhitespace(char *input);

void	center(char *input, t_shell *sh)
{
	sh->cmds = NULL;
	input = varlib_execute(input, sh);
	switch_caracters(&input);
	sh->cmds = ft_buildlst(input, sh);
	execution_part(sh);
	clean(sh, false, sh->exit, NULL);
}

void	prompt(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_ml_sigdefault(SIG_STATE_MAIN);
		shell->stop = 0;
		input = readline("minishell >$ ");
		if (!input)
		{
			if (input)
				free(input);
			clean(shell, true, 0, "exit\n");
		}
		if (isallwhitespace(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		ft_syntax_checker(input, shell);
		center(input, shell);
	}
}

int	main(int c, char **v, char **envp)
{
	t_shell	shell;

	(void)c;
	(void)v;
	shell.env = set_env(envp);
	shell.exit = 0;
	shell.stop = 0;
	shell.envp = envp;
	shell.cmds = NULL;
	prompt(&shell);
	(void)(envp);
	return (0);
}
