/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:13:43 by pedromota         #+#    #+#             */
/*   Updated: 2023/11/04 13:14:03 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_part_str(char *str, const char *remove);
void	update_pwd_values(t_env **env, char *oldpwd, char *pwd);
char	*get_pwd_from_list(t_env *env);
int		check_repetition(t_env *new, t_env **env);

void	change_to_home(void)
{
	if (chdir(getenv("HOME")) < 0)
		write(2, "Minishell: cd: HOME not set\n", 28);
}

void	change_to_oldpwd(void)
{
	if (chdir(getenv("OLDPWD")))
		printf("error changing directory OLDPWD\n");
}

void	change_to_directory(char *dir)
{
	if (chdir(dir))
		printf("error changing directory\n");
}

int	ft_cd(t_cmds *node)
{
	char *pwd;
	char *oldpwd;

	oldpwd = get_pwd_from_list(node->sh->env);
	if (!node->args || !node->args[0])
	{
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(node->args[0], "cd", 2))
	{
		if (!node->args[1] || node->args[1][0] == '~')
			change_to_home();
		else if (node->args[2])
			write(2, "Minishell: cd : too many arguments\n", 35);
		else if (node->args[1][0] == '-')
			change_to_oldpwd();
		else
			change_to_directory(node->args[1]);
		pwd = getcwd(NULL, 0);
		update_pwd_values(&node->sh->env, oldpwd, pwd);
		return (1);
	}
	return (0);
}