/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:16:59 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:15:21 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char *input, t_shell *sh)
{
	sh->cmds = NULL;
	input = varlib_execute(input, sh);
	switch_caracters(&input);
	sh->cmds = ft_buildlst(input, sh);
	software(sh);
	clean(sh, false, sh->exit, NULL);
	free(input);
	(void)sh;
}

void	prompt(t_shell *shell)
{
	char	*input;

	while (1)
	{
		printf("%sMain Process%s: %d\n",RED,RESET, getpid());
		input = readline("minishell >$ ");
		if (!input || !ft_strcmp(input, "exit"))
		{
			if (input)
				free(input);
			ft_env_delete(&shell->env);
			write(1, "Exit\n", 6);
			exit(0);
		}
		add_history(input);
		ft_syntax_checker(input, shell);
		init(input, shell);
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
	handle_quit(0, &shell);
	handle_sign(0, &shell);
	ft_ml_sigdefault();
	prompt(&shell);
	(void)(envp);
	return (0);
}
