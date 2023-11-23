/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:43 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/23 22:48:12 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_part_str(char *str, const char *remove);
void	update_pwd_values(t_env **env, char *oldpwd, char *pwd);
char	*get_pwd_from_list(t_env *env);
int		check_repetition(t_env *new, t_env **env);

char	*get_pwd_from_list(t_env *env)
{
	while (env)
	{
		if (strcmp(env->vars[0], "PWD") == 0)
			return (env->vars[1]);
		env = env->next;
	}
	return (NULL);
}

void	update_pwd_values(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*new_node;
	char	*oldpwd_str;
	char	*pwd_str;

	pwd_str = ft_strjoin("PWD=", pwd);
	oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
	new_node = ft_env_add(oldpwd_str);
	if (check_repetition(new_node, env) == 0)
		ft_ml_envadd_back(env, new_node);
	new_node = ft_env_add(pwd_str);
	if (check_repetition(new_node, env) == 0)
		ft_ml_envadd_back(env, new_node);
}

void	remove_part_str(char *str, const char *remove)
{
	char	*pos;

	pos = ft_strnstr(str, remove, ft_strlen(remove));
	if (pos != NULL)
		ft_memmove(pos, pos + ft_strlen(remove),
			ft_strlen(pos + ft_strlen(remove)) + 1);
}
