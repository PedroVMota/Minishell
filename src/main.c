/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:16:59 by pedro             #+#    #+#             */
/*   Updated: 2023/11/02 22:35:22 by pedromota        ###   ########.fr       */
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

char	*bash_prompt_replicate(void)
{
	char	cwd[1024];
	char	*prompt;
	int		size;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return "Minishell $:";
	size =	(int)ft_strlen("Minishell") + ft_strlen(cwd) + ft_strlen("\033[1;32m")
		+ ft_strlen("\033[0m") + 4;
	prompt = ft_calloc(size + 1, sizeof(char));
	if (!prompt)
		return ("Minishell $:");
	ft_strlcat(prompt, "\033[1;32m", size + 1);
	ft_strlcat(prompt, "Minishell", size + 1);
	ft_strlcat(prompt, "\033[0m", size + 1);
	ft_strlcat(prompt, ":", size + 1);
	ft_strlcat(prompt, "\033[1;34m", size + 1);
	ft_strlcat(prompt, &cwd[0], (ft_strlen(cwd) + 1));
	ft_strlcat(prompt, "\033[0m", size + 1);
	ft_strlcat(prompt, "$ ", size + 1);
	return (prompt);
}

void	prompt(t_shell *shell)
{
	char	*input;
	char	*promp;

	while (1)
	{
		promp = bash_prompt_replicate();
		input = readline(promp);
		free(promp);
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
	handle_quit(0, &shell);
	handle_sign(0, &shell);
	ft_ml_sigdefault();
	prompt(&shell);
	(void)(envp);
	return (0);
}
