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

struct s_shell	g_shell;

t_cmds	*ft_build_command(char *input)
{
	t_cmds	*cmds;

	switch_caracters(input);
	cmds = ft_buildlst(input);
	return (cmds);
}

void	prompt(void)
{
	char	*input;
	t_cmds	*lst;

	lst = NULL;
	input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			if (input)
				free(input);
			ft_env_delete(&g_shell.env);
			write(1, "Exit\n", 6);
			exit(0);
		}
		add_history(input);
		ft_syntax_checker(input);
		lst = ft_build_command(input);
		CommandDisplay(lst);
		clean_commands(&lst);
		free(input);
	}
}

int	main(int c, char **v, char **envp)
{
	(void)c;
	(void)v;
	g_shell.env = set_env(envp);
	g_shell.exit = 0;
	rl_catch_signals = 0;
	ft_ml_sigdefault();
	prompt();
	return (0);
}
