/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sh->cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:25 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 19:11:05 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	set_redirects_to_zero(void)
// {
// 	sh()->redirect.infile = NULL;
// 	sh()->redirect.outfile = NULL;
// 	sh()->redirect.output = 0;
// 	sh()->redirect.input = 0;
// }
/*
int	execute_single_comand(t_shell *sh)
{
	pid_t   pid;

	printf("here is the comand: %s\n", sh->cmds->args[0]);

	pid = fork();
	if (pid == 0)
	{
		if (builtins(sh) == 1)
			printf("builtin executed \n") ;
		else if (execve(sh->cmds->args[0], sh->cmds->args, NULL) == -1)
		{
			ft_putstr_fd("sh->cmds not found: ", 2);
			ft_putendl_fd(sh->cmds->args[0], 2);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		int child_status;
		waitpid(pid, &child_status, 0); // Wait for the specific child process to exit
		if (WIFEXITED(child_status))
		   sh->exit = WEXITSTATUS(child_status);
		if (child_status == 0)
			printf("\nit worked i guess\n");
	}

	// set_redirects_to_zero();
	return (0);
}*/