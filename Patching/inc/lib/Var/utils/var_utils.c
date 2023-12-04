#include "vars.h"

void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	return (NULL);
}

bool	does_have_var(char *s)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	if(!s)
		return (false);
	while (s[index])
	{
		if (s[index] == '\'' && quote == 0)
			quote = s[index];
		else if (s[index] == '\'' && quote != 0)
			quote = 0;
		else if (s[index] == '$' && !quote)
			return (true);
		index++;
	}
	return (false);
}

int	varlib_start_position(char *ptr)
{
	int	index;

	index = 0;
	if (!ptr)
		return (0);
	while (ptr[index])
	{
		if (ptr[index] == QUOTE)
			return (-1);
		if (ptr[index] == '$' && ptr[index + 1] != '$')
			return (index);
		index++;
	}
	return (-1);
}

void *trash(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	return (NULL);
}
