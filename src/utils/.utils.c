#include "minishell.h"

bool	isbuiltin(t_cmds *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (true);
	return (false);
}


void print_shell_err(char *categorie, char *error_msg, int new_err, t_shell *sh)
{
	ft_putstr_fd("Minishell :", 2);
	ft_putstr_fd(categorie, 2);
	ft_putstr_fd(error_msg, 2);
	sh->exit = new_err;
}

void print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == '\3' || *ptr == '\6' || *ptr == '\7' || *ptr == '\4' || *ptr == '\1' || *ptr == '\2')
			printf("[%d]", *ptr);
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int print_split(char **ptr)
{
	int i;

	i = -1;

	printf("Split: [");
	while (ptr && ptr[++i])
	{
		print_special(ptr[i]);
		printf(", ");
	}
	printf("] | ");
	printf("Size: [%d]\n", i);
	return (i);
}