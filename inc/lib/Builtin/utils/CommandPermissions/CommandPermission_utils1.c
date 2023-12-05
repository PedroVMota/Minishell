#include <builtins.h>


bool f_perm(char *name, char **paths)
{
	if (access(name, F_OK) == 0)
	{
		free_split(paths, 0);
		return (true);
	}
	return (false);
}

int shell_update_exit_status_error(int _new_err, t_shell *sh)
{
	sh->exit = _new_err;
	return (sh->exit);
}

void add_directory(char **cmd)
{
	int i;
	char *old_cmd;

	i = -1;
	while (cmd[++i])
	{
		old_cmd = cmd[i];
		if (cmd[i][ft_strlen(cmd[i]) - 1] == '/')
			continue;
		cmd[i] = ft_strjoin(cmd[i], "/");
		if (!cmd[i])
			return;
		free(old_cmd);
	}
}