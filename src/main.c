/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:16:59 by pedro             #+#    #+#             */
/*   Updated: 2023/09/25 13:13:22 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(char *input, t_shell *sh)
{
	sh->cmds = NULL;
	switch_caracters(input);
	sh->cmds = ft_buildlst(input, sh);
	software(sh);
	CommandDisplay(sh->cmds);
	clean_commands(&sh->cmds);
	free(input);
}

void	prompt(t_shell *shell)
{
	char	*input;
	clock_t	start;

	input = NULL;
	while (1)
	{
		start = clock();
		input = readline("minishell$ ");
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
		execution(input, shell);
		clock_t	end = clock();
		//timer in seconds
		double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
		printf("%sBenchmark: %.2fs%s\n",HBLU, time_spent, RESET);
	}
}

int	main(int c, char **v, char **envp)
{
	t_shell	shell;

	(void)c;
	(void)v;
	shell.env = set_env(envp);
	shell.exit = 0;
	// rl_catch_signals = 0;
	ft_ml_sigdefault();
	prompt(&shell);
	(void)(envp);
	return (0);
}
