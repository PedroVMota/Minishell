/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:47:20 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 21:55:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

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

int	ft_cd_helper(t_cmds *node)
{
	if (node->args[1] && node->args[1][1])
	{
		if (node->args[1][1] == '/')
		{
			remove_part_str(&node->args[1], "~/");
			change_to_home();
			change_to_directory(node->args[1]);
		}
		else
		{
			write(2, "Minishell: cd: No such file or directory\n", 42);
			return (1);
		}
	}
	else
		change_to_home();
	return (0);
}

// heredoc(node,node->infiles->element[1]);
// this was on the line 61 for some reason explain to me tommorow
int	ft_cd(t_cmds *node)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = get_pwd_from_list(node->sh->env);
	pwd = NULL;
	if (check_nothing(node) == 1)
		return (1);
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
	update_pwd_values(&node->sh->env, oldpwd, pwd);
	return (0);
}
