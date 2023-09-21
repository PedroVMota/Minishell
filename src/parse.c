#include <minishell.h>

void	var_replacer(char **str)
{
	int varcounter;
	int varselector;
	int strselector;

	varselector = 0;
	varcounter = 0;
	strselector = 0;
	while (str[strselector])
	{
		varcounter = variable_counter(str[strselector]);
		while (varselector < varcounter)
		{
			str[strselector] = varcheckvalid(str[strselector]);
			varselector++;
		}
		strselector++;
	}
	print_split(str);
}

void parse(t_cmds *node)
{
	while (node)
	{
		print_split(node->args);
		var_replacer(node->args);
		node = node->next;
	}
}