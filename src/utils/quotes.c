#include <minishell.h>

void quote_delete_str(char **input, char c)
{
	char *temp;
	int i;
	int j;
	int flag;

	i = -1;
	j = 0;
	flag = 0;
	temp = ft_calloc(ft_strlen(*input) + 1, 1);
	if (!temp)
		return;
	while (input[0][++i])
	{
		if ((input[0][i] == '\'' || input[0][i] == '\"') && (!c || c == input[0][i]) && (!flag || flag == input[0][i]))
			c = input[0][i] * (c != input[0][i]);
		else
			temp[j++] = input[0][i];
		if (c)
			flag = c;
		else
			flag = 0;
	}
	free(*input);
	*input = temp;
}

void	del_quotes(char **input)
{
	int	k;

	k = -1;
	while (input[++k])
	{
		if (ft_strchr(input[k], '\'') || ft_strchr(input[k], '\"'))
			quote_delete_str(&input[k], 0);
	}
}

void	syntax_quotes(char *input, int i, int *flag)
{
	char	c;

	c = input[i];
	*flag = c;
	while (input[++i])
	{
		if (c == input[i])
			return ;
	}
	syntax_report(&c, input, 1);
}