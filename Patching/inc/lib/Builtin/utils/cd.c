/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:47:20 by pedro             #+#    #+#             */
/*   Updated: 2023/12/04 16:00:38 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_part_str(char *str, const char *remove);
void update_pwd_values(t_env **env, char *oldpwd, char *pwd);
char *get_pwd_from_list(t_env *env);
int check_repetition(t_env *new, t_env **env);
int check_nothing(t_cmds *node);

void change_to_home(void)
{
	if (chdir(getenv("HOME")) < 0)
		write(2, "Minishell: cd: HOME not set\n", 28);
}

void change_to_oldpwd(void)
{
	if (chdir(getenv("OLDPWD")))
		printf("error changing directory OLDPWD\n");
}

void change_to_directory(char *dir)
{
	if (chdir(dir))
		printf("error changing directory\n");
}

int ft_cd_helper(t_cmds *node)
{
	if (node->args[1] && node->args[1][1])
	{
		if (node->args[1][1] == '/')
			remove_part_str(node->args[1], "~/");
		else
		{
			write(2, "Minishell: cd: No such file or directory\n", 43);
			return (1);
		}
		change_to_home();
		change_to_directory(node->args[1]);
	}
	else
		change_to_home();
	return (0);
}

int ft_cd(t_cmds *node)
{
	char *pwd;
	char *oldpwd;
	int *dups;

	redirect(node);
	dups = set_dups(node);
	oldpwd = get_pwd_from_list(node->sh->env);
	if (check_nothing(node) == 1)
		return (1);
	if (!ft_strncmp(node->args[0], "cd", 2))
	{
		if (!node->args[1] || node->args[1][0] == '~')
		{
			if (ft_cd_helper(node) == 1)
				return (1);
		}
		else if (node->args[2])
			write(2, "Minishell: cd : too many arguments\n", 35);
		else if (node->args[1][0] == '-')
			change_to_oldpwd();
		else
			change_to_directory(node->args[1]);
		pwd = getcwd(NULL, 0);
		update_pwd_values(&node->sh->env, oldpwd, pwd);
		free(pwd);
		if (dups[0] != -10)
			close(dups[0]);
		if (dups[1] != -10)
			close(dups[1]);
		return (1);
	}
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	return (0);
}
