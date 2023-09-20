#include <minishell.h>

static char replace(char c)
{
	if(c == '|')
		return TOKEN_PIPE;
	if(c == '>')
		return TOKEN_OUT;
	if(c == '<')
		return TOKEN_IN;
	if(c == ';')
		return TOKEN_SEMI_COLOM;
	if(c == ' ')
		return TOKEN_SPACE;
	if(c == '\"')
		return TOKEN_DQUOTE;
	if(c == '\'')
		return TOKEN_QUOTE;
	return c;
}

void switch_caracters(char *ptr)
{
	t_mode arr[2];

	arr[0] = ENV_MODE_TOKEN;
	if(!ptr)
		return ;
	while (ptr && *ptr)
	{
		arr[1] = arr[0];
		ft_mode_changer_ascii(*ptr, &arr[0]);
		if ((arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_TOKEN) \
		|| ((arr[0] == ENV_MODE_DQUOTE && arr[1] == ENV_MODE_TOKEN) \
		|| (arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_DQUOTE)) \
		|| ((arr[0] == ENV_MODE_QUOTE && arr[1] == ENV_MODE_TOKEN) \
		|| (arr[0] == ENV_MODE_TOKEN && arr[1] == ENV_MODE_QUOTE)))
			*ptr = replace(*ptr);
		ptr++;
	}
}