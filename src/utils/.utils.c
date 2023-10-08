#include <minishell.h>

void	CommandDisplay(t_cmds *ptr)
{
	pid_t	id;
	int		command;
	int		report;
	int		stat;

	if(!ptr)
		return ;
	id = fork();

	if (id == 0)
	{
		if(!ptr)
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
		while (ptr)
		{
			printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
			printf("Command: %d\n", command);
			printf("Current command: ");
			print_split(ptr->args);
			printf("Pipe[0] = %d\n", ptr->pipe[0]);
			printf("Pipe[1] = %d\n", ptr->pipe[1]);
			printf("redi[0] = %d\n", ptr->redirection[0]);
			printf("redi[1] = %d\n", ptr->redirection[1]);
			ptr = ptr->next;
			command++;
		}
		unlink("List.txt");
		close(report); // Close the file descriptor
		exit(0);
	}
	stat = 0;
	waitpid(id, &stat, 0);
	if (stat != 0)
		printf("List Command Error: ");
}

void	print_special(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == PIPE || *ptr == OUTAPP || *ptr == INFILE
			|| *ptr == SEMI_COLOM || *ptr == SPACE
			|| *ptr == DQUOTE || *ptr == QUOTE)
			printf("[%d]", *ptr);
		else
			printf("%c", *ptr);
		ptr++;
	}
}

int	print_split(char **ptr)
{
	int	i;

	i = -1;
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
