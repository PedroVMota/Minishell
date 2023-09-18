#include <minishell.h>

t_cmds	*ft_build_command(char *input)
{
	t_cmds *cmds;
	char **ptr;
	int len;

	switch_caracters(input);
	cmds = NULL;
	ptr = ft_split(input, TOKEN_PIPE);
	cmds = ft_buildlst(input);
	// CommandDisplay(cmds);
	clean_commands(&cmds);
	free_split(ptr);
}