#include "minishell.h"

static t_env	*get_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_env_add(char *str)
{
	t_env	*new;
	char	**split;

	split = ft_split(str, '=');
	if (!split)
		return (NULL);
	free(str);
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->vars = split;
	new->next = NULL;
	return (new);
}

void	ft_ml_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = get_last(*lst);
	last->next = new;
}

t_env	*set_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
		ft_ml_envadd_back(&env, ft_env_add(ft_strdup(envp[i])));
	return (env);
}
