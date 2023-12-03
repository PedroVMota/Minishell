#include "minishell.h"

void	center(char *input, t_shell *sh)
{
	sh->cmds = NULL;
	input = varlib_execute(input, sh);
	switch_caracters(&input);
	sh->cmds = ft_buildlst(input, sh);
	execution_part(sh);
	clean(sh, false, sh->exit, NULL);
}

bool	isallwhitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

void	prompt(t_shell *shell)
{
	char	*input;
	char	*exit;

	while (1)
	{
		exit = ft_itoa(shell->exit);
		info(exit, MAG);
		free(exit);
		input = readline("minishell >$ ");
		if (!input || !ft_strcmp(input, "exit"))
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
	handle_quit(0, &shell);
	handle_sign(0, &shell);
	ft_ml_sigdefault();
	prompt(&shell);
	(void)(envp);
	return (0);
}
