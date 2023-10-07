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

struct s_shell g_shell;

t_cmds *execution(char *input)
{
	t_cmds *cmds;

	switch_caracters(input);
	cmds = ft_buildlst(input);
	if(!cmds)
		return NULL;

	CommandDisplay(cmds);

	return cmds;
}

void prompt(void)
{
	char *input;
	t_cmds *ptr;

	input = NULL;
	int attempt = 0;
	while (1)
	{
		printf("Tentativa %d\n", attempt);
		displayerror(input);
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
		ptr = execution(input);
		clean_commands(&ptr);
		free(input);
		attempt++;
	}
}

int main(int c, char **v, char **envp)
{
	(void)c;
	(void)v;
	g_shell.env = set_env(envp);
	g_shell.exit = 0;
	rl_catch_signals = 0;
	ft_ml_sigdefault();
	prompt();
	printf("%sDIOS%s", GRN, RESET);
	return (0);
}
