#include "minishell.h"

static char	*update_old_str(char *old, char *new, int pre_or_suf)
{
	if (pre_or_suf == 0)
		return (ft_strjoin(new, old));
	else if (pre_or_suf == 1)
		return (ft_strjoin(old, new));
	free(old);
	return (NULL);
}

char	*replace_home(void)
{
	char	*home;
	char	path[1024];

	if (getcwd(path, sizeof(path)) == NULL)
		return ("Minishell $> ");
	home = getenv("HOME");
	if (!home)
		return (NULL);
	if (home != NULL && strncmp(path, home, strlen(home)) == 0)
	{
		memmove(path + 1, path + strlen(home), strlen(path) - strlen(home) + 1);
		path[0] = '~';
	}
	return (ft_strdup(path));
}

char	*bash_prompt_replicate(void)
{
	char	*path;
	char	*user;
	char	*final;

	
	user = getenv("USER");
	if (!user)
		return ("Minishell $> ");
    path = replace_home();
	if (!path)
		return ("Minishell $> ");
	final = ft_strdup(BGRN);
	final = update_old_str(final, user, 1);
	final = update_old_str(final, RESET, 1);
	final = update_old_str(final, ":", 1);
	final = update_old_str(final, BBLU, 1);
	final = update_old_str(final, path, 1);
	final = update_old_str(final, RESET, 1);
	final = update_old_str(final, ": $ ", 1);
	free(path);
	return (final);
}