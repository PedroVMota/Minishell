#include <minishell.h>

void	print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == TOKEN_PIPE || *ptr == TOKEN_OUT || *ptr == TOKEN_IN
			|| *ptr == TOKEN_SEMI_COLOM || *ptr == TOKEN_SPACE
			|| *ptr == TOKEN_DQUOTE || *ptr == TOKEN_QUOTE)
			printf("%s%d%s", RED, *ptr, RESET);
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int	print_split(char **ptr)
{
	int	i;

	i = 0;
	printf("%sSplit: [%s", YEL, RESET);
	while (ptr[i])
	{
		print_special(ptr[i]);
		printf(", ");
		i++;
	}
	printf("%s]%s\n", YEL, RESET);
	printf("%sSize: [%d]%s\n", YEL, i, RESET);
	return (i);
}

void	SplitClean(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**args_parser(char **input)
{
	char	**ptr;
	int		len;

	ptr = ft_split(*input, TOKEN_SPACE);
	len = print_split(ptr);
	SplitClean(ptr);
	return (ptr);
}

void	LinkNode(t_cmds *recent, t_cmds *new)
{
	if (!new)
	{
		new->next = NULL;	
		new->prev = NULL;
		return ;
	}
	else if (!new)
	{
		new->prev = NULL;
		return ;
	}
	else
	{
		recent->prev = new;
		new->next = recent;
		new->prev = NULL;
	}
}

t_cmds	*NodeCreate(char **input, t_cmds *cur)
{
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	cmd->args = args_parser(input);
	// LinkNode(cur, cmd);
	return (cmd);
}

t_cmds	*ft_build_command(char *input)
{
	t_cmds *cmds;
	char **ptr;
	int len;

	switch_caracters(input);
	ptr = ft_split(input, TOKEN_PIPE);
	len = -1;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	while (++len)
	{
		printf("%sCommand: [%s%s%s]%s\n", YEL, RESET, ptr[len], YEL, RESET);
		cmds = NodeCreate(&ptr[len], cmds);
	}
	SplitClean(ptr);
}