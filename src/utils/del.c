#include <minishell.h>

int	free_split(char **split, int ret)
{
	char	**ptr;

	ptr = split;
	if (!split)
		return (1);
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
	return (ret);
}

void	clean_redirection(t_redirections **head)
{
	t_redirections	*local;
	t_redirections	*next;

	local = *head;
	if (!local)
		info("No redirections to clean", MAG);
	while (local)
	{
		free_split(local->element, 0);
		next = local->next;
		free(local);
		local = next;
	}
}

static void	close_fds(t_cmds *cmds)
{
	if (cmds->pipe[0] != -1)
		close(cmds->pipe[0]);
	if (cmds->pipe[1] != -1)
		close(cmds->pipe[1]);
	if (cmds->redirection[0] != -1)
		close(cmds->redirection[0]);
	if (cmds->redirection[1] != -1)
		close(cmds->redirection[1]);
}

int	ft_env_delete(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free_split((*env)->vars, 1);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}

void	close_redi(t_cmds *node)
{
	if (node->redirection[0] != -1 && node->redirection[0] != 2)
		close(node->redirection[0]);
	if (node->redirection[1] != -1 && node->redirection[1] != 2)
		close(node->redirection[1]);
	if (node->is_builtin == 1)
	{
		if (node->saved_stdin != -1)
		{
			dup2(node->saved_stdin, 0);
			close(node->saved_stdin);
			node->saved_stdin = -1;
		}
		if (node->saved_stdout != -1)
		{
			dup2(node->saved_stdout, 1);
			close(node->saved_stdout);
			node->saved_stdout = -1;
		}
	}
}

int	clean(t_shell *sh, bool _exit, int status, char *msg)
{
	t_cmds *cmds;
	t_cmds *tmp;

	tmp = NULL;
	cmds = NULL;
	if (sh)
		cmds = sh->cmds;
	while (sh && cmds)
	{
		clean_redirection(&cmds->infiles);
		clean_redirection(&cmds->outfile);
		close_fds(cmds);
		close_redi(cmds);
		free_split(cmds->args, 1);
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	if (_exit)
	{
		if (msg)
			write(2, msg, ft_strlen(msg));
		ft_env_delete(&sh->env);
		exit(status);
	}
	return (0);
}