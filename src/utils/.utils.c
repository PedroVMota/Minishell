#include <minishell.h>

void	CommandDisplay(t_cmds *ptr)
{
	t_cmds	*head;

	head = ptr;
	if (!head)
	{
		printf("There is no t_cmds\n");
		return ;
	}
	while (head)
	{
		if (!head)
			break ;
		printf("%s_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*%s\n", YEL, RESET);
		printf("%sCommand%s = %s\n", MAG, RESET, head->args[0]);
		printf("%sPipe[0]%s = %d\n", MAG, RESET, head->pipe[0]);
		printf("%sPipe[1]%s = %d\n", MAG, RESET, head->pipe[1]);
		printf("%sredi[0]%s = %d\n", MAG, RESET, head->redirection[0]);
		printf("%sredi[1]%s = %d\n", MAG, RESET, head->redirection[1]);
		head = head->next;
	}
	printf("%sExit Status%s: %d\n", HBLU, RESET, ptr->sh->exit);
}
static char	*convert_char(char a)
{
	if (a == '\1')
		return ("\e[0;31mDQUOTE\e[0;36m");
	if (a == '\2')
		return ("\e[0;31mSQUOTE\e[0;36m");
	if (a == '\3')
		return ("\e[0;35mPIPE\e[0;36m");
	if (a == '\4')
		return ("\e[0;36mSPACE\e[0;36m");
	if (a == '\6')
		return ("\e[0;37mOUTTRUC\e[0;36m");
	if (a == '\7')
		return ("\e[0;37mINFILE\e[0;36m");
	if (a == '\b')
		return ("\e[0;37mHEREDOC\e[0;36m");
	return ("");
}

void	print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == '\1' || *ptr == '\2' || *ptr == '\3' || *ptr == '\4'
			|| *ptr == '\6' || *ptr == '\7' || *ptr == '\b')
			printf("%s[%s]%s", CYN, convert_char(*ptr), RESET);
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int	print_split(char **ptr)
{
	int	i;

	i = -1;
	if (!ptr)
		return (printf("%sThere is no char **%s\n", RED, RESET));
	printf("{\n");
	while (ptr && ptr[++i])
	{
		printf("\tArg[%d]: ", i);
		print_special(ptr[i]);
		printf(";\n");
	}
	printf("}\n");
	return (i);
}
