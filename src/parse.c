#include <minishell.h>


t_cmds *ft_build_command(char *input)
{
	printf("%s\n", input);
	switch_caracters(input);
	printf("%s\n", input);

}