#include "minishell.h"

int check_sep(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
		arr[0] = 1;
	return (arr[0]);
}

void parse(char *res, char *str, char sep, int *arr)
{
	int len;

	len = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '\"') && (!sep || sep == *str))
			sep = (*str) * (sep != *str);
		else if (*str == ' ' && !sep)
			*str = 2;
		if (!sep && check_sep(str, arr))
		{
			*res++ = 2;
			*res++ = (3 - (*str != '|' || len != 0 || arr[1] == 0));
			if ((*str != '|' || !arr[1]) || len)
				*res++ = *str;
			if (str++ && *str != '|' && arr[0] == 2)
				*res++ = *str++;
			*res++ = 2;
			len++;
		}
		// else if ((*str == 2 && arr[1]) ||
				//  ((*str != 2 || *str++ != 2) && ++arr[1]))
		// {
			// len = !(!!(*res++ = *str++));
		// }
	}
	printf("res: %s\n", &res[0]);
}

t_cmds *ft_build_command(char *input)
{
	char *res = NULL;
	int arr[2];

	arr[0] = 0;
	arr[1] = 0;
	res = ft_calloc((ft_strlen(input) * 3 + 1), 1);
	if (!res)
		return NULL;
	parse(res, input, 0, arr);
	printf("%sInput Size: %ld\nAllocation: %ld\nString: %s%s", RED, ft_strlen(input), ft_strlen(input) * 3 + 1, res,RESET);


	return NULL;
}
