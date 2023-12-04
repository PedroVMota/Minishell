/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:43 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/04 15:59:33 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_part_str(char *str, const char *remove);
void update_pwd_values(t_env **env, char *oldpwd, char *pwd);
char *get_pwd_from_list(t_env *env);
int check_repetition(t_env *new, t_env **env);

char *get_pwd_from_list(t_env *env)
{
	while (env)
	{
		if (strcmp(env->vars[0], "PWD") == 0)
			return (env->vars[1]);
		env = env->next;
	}
	return (NULL);
}

void search_env_for_update(t_env **head, char *search_name)
{
	if(!(*head))
		return ;
	while (*head)
	{
		if (ft_strcmp((*head)->vars[0], search_name) == 0)
			return;
		(*head) = (*head)->next;
	}
	return;
}

void update_pwd_values(t_env **env, char *oldpwd, char *pwd)
{
	// t_env	*new_node;
	// char	*oldpwd_str;
	// char	*pwd_str;

	// pwd_str = ft_strjoin("PWD=", pwd);
	// oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
	// new_node = ft_env_add(oldpwd_str);
	// if (check_repetition(new_node, env) == 0)
	// 	ft_ml_envadd_back(env, new_node);
	// new_node = ft_env_add(pwd_str);
	// if (check_repetition(new_node, env) == 0)
	// 	ft_ml_envadd_back(env, new_node);

	t_env *pwdenv;
	t_env *oldpwdenv;
	oldpwdenv = *env;
	pwdenv = *env;
	search_env_for_update(&oldpwdenv, "OLDPWD");
	search_env_for_update(&pwdenv, "PWD");
	if (pwdenv)
	{
		if(pwdenv->vars[1])
			free(pwdenv->vars[1]);
		pwdenv->vars[1] = pwd;
	}
	if (oldpwdenv)
	{
		if(oldpwdenv->vars[1])
			free(oldpwdenv->vars[1]);
		oldpwdenv->vars[1] = oldpwd;
	}
}

void remove_part_str(char *str, const char *remove)
{
	char *pos;

	pos = ft_strnstr(str, remove, ft_strlen(remove));
	if (pos != NULL)
		ft_memmove(pos, pos + ft_strlen(remove),
				   ft_strlen(pos + ft_strlen(remove)) + 1);
}

int check_nothing(t_cmds *node)
{
	if (!node->args || !node->args[0])
	{
		printf("\n");
		return (1);
	}
	return (0);
}
