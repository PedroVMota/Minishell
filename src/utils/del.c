#include <minishell.h>

void free_split(char **split)
{
	char **ptr = split;
	if(!split)
		return ;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
}

void clean_commands(t_cmds **cmds)
{
	t_cmds *ptr;
	t_cmds *next;

	next = NULL;
	ptr = *cmds;
	while (ptr)
	{
		free_split(ptr->args);
		if (ptr->pipe[0] != -1)
			close(ptr->pipe[0]);
		if (ptr->pipe[1] != -1)
			close(ptr->pipe[1]);
		if (ptr->redirection[0] != -1)
			close(ptr->redirection[0]);
		if (ptr->redirection[1] != -1)
			close(ptr->redirection[1]);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}

int ft_env_delete(t_env **env)
{
	t_env *tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free_split((*env)->vars);
		free((*env));
		(*env) = tmp;
	}
	return (1);
}