#include <minishell.h>

void CommandDisplay(t_cmds *ptr)
{
	pid_t id;
	int command;
	int report;
	int stat;

	if (!ptr)
		return;
	id = fork();

	if (id == 0)
	{
		if (!ptr)
			exit(1);
		command = 0;
		report = open("lst.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (report == -1)
		{
			printf("No file\n");
			exit(1);
		}
		if (dup2(report, STDOUT_FILENO) == -1) // Check for error
		{
			printf("Dup2Error\n");
			exit(1);
		}
		t_cmds *head = ptr;
		while (head)
		{
			printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
			printf("Command: %d\n", command);
			printf("Current command: ");
			print_split(head->args);
			printf("Pipe[0] = %d\n", head->pipe[0]);
			printf("Pipe[1] = %d\n", head->pipe[1]);
			printf("redi[0] = %d\n", head->redirection[0]);
			printf("redi[1] = %d\n", head->redirection[1]);
			head = head->next;
			command++;
		}
		printf("Exit Status: %d\n", ptr->sh->exit);
		unlink("List.txt");
		close(report); // Close the file descriptor
		clean(ptr->sh, true, ptr->sh->exit);
		exit(0);
	}
	stat = 0;
	waitpid(id, &stat, 0);
	if (stat != 0)
		printf("List Command Error: ");
}

static char *convert_char(char a)
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
}

void print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == '\1' || *ptr == '\2' || *ptr == '\3' || *ptr == '\4' || *ptr == '\6' || *ptr == '\7' || *ptr == '\b')
			printf("%s[%s]%s", CYN, convert_char(*ptr), RESET);
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int print_split(char **ptr)
{
	int i;

	i = -1;
	if (!ptr)
		return printf("%sThere is no char **%s\n", RED, RESET);
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
