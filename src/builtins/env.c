#include "minishell.h"

static void	outfile(t_cmds *node)
{
	int	fd;

	fd = 1;
	if (node->next)
		fd = node->pipe[1];
	if (node->redirection[1] != -1)
		fd = node->redirection[1];
	if (dup2(fd, 1) == -1)
	{
		write(2, "Minishell: ", 12);
		perror("dup2");
		exit(1);
	}
	if (node->prev)
		close(node->prev->pipe[0]);
	if (node->pipe[0] != -1)
		close(node->pipe[0]);
	if (node->pipe[1] != -1)
		close(node->pipe[1]);
	if (node->redirection[0] != -1)
		close(node->redirection[0]);
	if (node->redirection[1] != -1)
		close(node->redirection[1]);
}

/// @brief This function is used to execute the command
/// @param node  The command node
/// @return exit status
int	ft_env(t_cmds *node)
{
	t_env *env;

	env = node->sh->env;
	outfile(node);
	while (env)
	{
		printf("%s=%s\n", env->vars[0], env->vars[1]);
		env = env->next;
	}
	exit(0);
	return (0);
}