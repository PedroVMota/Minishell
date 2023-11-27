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

void	print_shell_err(char *categorie, char *error_msg, int new_err,
		t_shell *sh)
{
	ft_putstr_fd("Minishell :", 2);
	ft_putstr_fd(categorie, 2);
	ft_putstr_fd(error_msg, 2);
	sh->exit = new_err;
}

char	*convert_to_char(char c)
{
	if (c == '\1')
		return ("\e[0;31mDouble\e[0m");
	if (c == '\2')
		return ("\e[0;31mSingle\e[0m");
	if (c == '\3')
		return ("\e[0;31mPipe\e[0m");
	if (c == '\4')
		return ("\e[0;31mSpace\e[0m");
	if (c == '\6')
		return ("\e[0;31mOUTTRUC\e[0m");
	if (c == '\7')
		return ("\e[0;31mINFILE\e[0m");
	if (c == '\b')
		return ("\e[0;31mHeredoc\e[0m");
	if (c == ' ')
		return ("C_SPACE");
	return ("");
}

void	print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == '\3' || *ptr == '\6' || *ptr == '\7' || *ptr == '\4'
			|| *ptr == '\1' || *ptr == '\2' || *ptr == ' ')
			printf("[%s]", convert_to_char(*ptr));
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int	print_split(char **ptr)
{
	int	i;

	i = -1;
	printf("Split: [");
	while (ptr && ptr[++i])
	{
		print_special(ptr[i]);
		printf(", ");
	}
	printf("] | ");
	printf("Size: [%d] ", i);
	return (i);
}

void	ShowCommands(t_cmds *cmd)
{
	int				Command;
	int				Redirection;
	t_redirections	*r;

	Command = 0;
	Redirection = 0;
	r = NULL;
	if (!cmd)
	{
		printf("There is no command\n");
		return ;
	}
	while (cmd)
	{
		r = cmd->reds;
		Redirection = 0;
		Command++;
		printf("==================== Command %d ====================\n",
			Command);
		printf("Command:{%s}\n", cmd->args[0]);
		cmd = cmd->next;
		if (!r)
			continue ;
		while (r)
		{
			Redirection++;
			printf("------> Redirection {%d}: ", Redirection);
			printf("Type -> %d\n", r->mode);
			print_split(r->element);
			printf("\n");
			r = r->next;
		}
		r = NULL;
	}
}

int	size_of_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	ShowSingleCommand(t_cmds *cmd)
{
	int Command;
	int Redirection;
	t_redirections *r;

	Command = 0;
	Redirection = 0;
	r = NULL;
	if (!cmd)
	{
		printf("There is no command\n");
		return ;
	}
	r = cmd->reds;
	Redirection = 0;
	Command++;
	printf("==================== Command %d ====================\n", Command);
	printf("Command: ");
	print_split(cmd->args);
	printf("\n");
	printf("Size: [%d]\n", size_of_split(cmd->args));
	cmd = cmd->next;
	if (!r)
		return ;
	while (r)
	{
		Redirection++;
		printf("------> Redirection {%d}: ", Redirection);
		printf("Type -> %d\n", r->mode);
		print_split(r->element);
		printf("\n");
		r = r->next;
	}
}