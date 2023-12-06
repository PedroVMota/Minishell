/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:43 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 05:40:55 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

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

void	search_env_for_update(t_env **head, char *search_name)
{
	if (!(*head))
		return ;
	while (*head)
	{
		if (ft_strcmp((*head)->vars[0], search_name) == 0)
			return ;
		(*head) = (*head)->next;
	}
	return ;
}

void	update_pwd_values(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*pwdenv;
	t_env	*oldpwdenv;

	pwd = getcwd(NULL, 0);
	oldpwdenv = *env;
	pwdenv = *env;
	search_env_for_update(&oldpwdenv, "OLDPWD");
	search_env_for_update(&pwdenv, "PWD");
	if (pwdenv)
	{
		pwdenv->vars[1] = pwd;
	}
	if (oldpwdenv)
	{
		free(oldpwdenv->vars[1]);
		oldpwdenv->vars[1] = oldpwd;
	}
}

void	remove_part_str(char **str, const char *remove)
{
	char	*s;
	char	*sb;

	sb = *str;
	(void)remove;
	s = ft_strdup(&sb[2]);
	if (!s)
		return ;
	free(*str);
	*str = s;
}

int	check_nothing(t_cmds *node)
{
	if (!node->args || !node->args[0])
	{
		printf("\n");
		return (1);
	}
	return (0);
}
