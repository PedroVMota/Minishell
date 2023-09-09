#include "minishell.h"


void toggle(char l, t_mode *stat)
{
	if(l == '\"' && *stat == ENV_MODE_TOKEN)
		*stat == ENV_MODE_DQUOTE;
	else if (l == '\'' && *stat == ENV_MODE_TOKEN)
		*stat == ENV_MODE_QUOTE;
	else if(l == '\"' && *stat == ENV_MODE_DQUOTE)
		*stat == ENV_MODE_TOKEN;
	else if(l == '\'' && *stat == ENV_MODE_QUOTE)
		*stat == ENV_MODE_TOKEN;
}

static void replace_especial_characters(char *in)
{
	t_mode new = ENV_MODE_TOKEN;
	t_mode old = ENV_MODE_TOKEN;
	int i;

	i = 0;
	while(in[i])
	{
		old = new;
		toggle(in[i], &new);
		if(in[i] == '')
	}
}


void ft_build_command(char *input)
{
	t_cmds *cmdlst;
	char *pre_split;
}
