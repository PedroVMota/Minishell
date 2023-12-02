#include <minishell.h>

bool	f_perm(char *name, char **paths)
{
	if (access(name, F_OK) == 0)
	{
		free_split(paths, 0);
		return (true);
	}
	return (false);
}
