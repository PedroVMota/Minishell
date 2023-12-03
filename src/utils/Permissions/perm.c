#include "minishell.h"

void	set_relative_path(t_cmds *head, int *err);
void	set_absolute_path(t_cmds *head, int *err);

int	check_all_paths(t_cmds *head, int *err, int *type)
{
	*type = 1;
	if (ft_strnstr(head->args[0], "./", 2) || ft_strnstr(head->args[0], "../",
			3))
		*type = 2;
	if (!isbuiltin(head) && *type == 1)
		set_relative_path(head, err);
	else if (*type == 2)
		set_absolute_path(head, err);
	return (0);
}

bool	permission_tester(t_cmds *head)
{
	int	type;

	type = 0;
	if(!head || !head->args || !head->args[0])
		return (false);
	check_all_paths(head, &head->sh->exit, &type);
	if (head->sh->exit == 127 && type == 1)
		return (false);
	else if (head->sh->exit == 127 && type == 2)
		return (false);
	else if (head->sh->exit == 126)
		return (false);
	return (true);
}
