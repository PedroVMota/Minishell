#include <minishell.h>

// Mode 0 nothing 1 string

void check(int mode, char *string);

char **parse(char **arr, t_cmds *node)
{
	int selector;

	selector = -1;
	print_split(arr);
	while (arr[++selector])
		var_replacer(&arr[selector]);
	print_split(arr);
	(void)node;
	return arr;
}