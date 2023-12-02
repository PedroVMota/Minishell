#include "minishell.h"

static int	check_options(t_cmds *node, int *word)
{
	int	break_line;

	break_line = 0;
	*word = 1;
	if (!node->args[1])
		return (0);
	if (node->args[*word][0] == '-' && node->args[*word][1] == 'n')
	{
		break_line = 1;
		(*word)++;
	}
	return (break_line);
}

int	ft_echo(t_cmds *node)
{
	int	word;
	int	br;

	redirect(node);
	br = check_options(node, &word);
	while (node->args[word])
	{
		if (node->args[word])
			write(1, node->args[word], ft_strlen(node->args[word]));
		if (node->args[word + 1])
			write(1, " ", 1);
		word++;
	}
	if (br == 0)
		printf("\n");
	if (node->next || node->prev)
		clean(node->sh, true, 0, NULL);
	else
		close_redi(node);
	return (0);
}
