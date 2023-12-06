#include <minishell.h>

char	replace(char c)
{
	if (c <= 0)
		return (c);
	else if (c > 126)
		return (c);
	if (c == '|')
		return ('\3');
	if (c == '>')
		return ('\6');
	if (c == '<')
		return ('\7');
	if (c == ' ')
		return ('\4');
	if (c == '\"')
		return ('\1');
	if (c == '\'')
		return ('\2');
	return (c);
}

void	inside_string_skip(char *beg, int *pos, bool *change)
{
	char	what_char;

	what_char = 0;
	if (beg[*pos] == '\"' || beg[*pos] == '\'')
	{
		what_char = beg[*pos];
		beg[*pos] = replace(beg[*pos]);
		*change = !(*change);
	}
	if (!*change)
	{
		while (beg[*pos])
		{
			if (beg[*pos] == what_char)
			{
				beg[*pos] = replace(beg[*pos]);
				*change = !(*change);
				break ;
			}
			(*pos)++;
		}
	}
}

void	switch_caracters(char **ptr)
{
	int		main;
	bool	change;

	main = 0;
	change = true;
	if(!ptr || !*ptr)
		return ;
	while ((*ptr)[main])
	{
		inside_string_skip((*ptr), &main, &change);
		if (change)
			(*ptr)[main] = replace((*ptr)[main]);
		main++;
	}
}
