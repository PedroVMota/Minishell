#include "minishell.h"

int	standard_choiser(t_cmds *cmd)
{
	if (cmd->redirection[0] != -1)
	{
		if (dup2(cmd->redirection[0], STDIN_FILENO) == -1)
			exit(1);
        close(cmd->redirection[0]);
	}
	if (cmd->redirection[1] != -1)
	{
		if (dup2(cmd->redirection[1], STDOUT_FILENO) == -1)
			exit(1);
        close(cmd->redirection[1]);
	}
	return (0);
}
