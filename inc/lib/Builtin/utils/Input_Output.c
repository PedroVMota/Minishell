/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input_Output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:10:52 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/08 13:28:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

int		out_append(t_redirections *node);
int		permission_checker(t_redirections *node, t_cmds *cmds);
void	update_signal_for_child(t_cmds *cmd);

void	set_infile(t_redirections *in, t_cmds *node)
{
	while (in)
	{
		if (node->is_builtin == 1)
			node->saved_stdin = dup(0);
		if (node->redirection[0] > 0)
			close(node->redirection[0]);
		node->redirection[0] = permission_checker(in, node);
		if (node->redirection[0] == -2)
			clean(node->sh, true, 1, NULL);
		in = in->next;
	}
}

void	set_output(t_redirections *out, t_cmds *node)
{
	while (out)
	{
		if (node->is_builtin == 1)
			node->saved_stdout = dup(1);
		if (node->redirection[1] > 0)
			close(node->redirection[1]);
		node->redirection[1] = permission_checker(out, node);
		if (node->redirection[1] == -2)
			clean(node->sh, true, 1, NULL);
		out = out->next;
	}
}

void	redirect(t_cmds *node)
{
	t_redirections	*in;
	t_redirections	*out;

	in = node->infiles;
	out = node->outfile;
	set_infile(in, node);
	set_output(out, node);
	if (node->redirection[1] == -2)
		clean(node->sh, true, 1, NULL);
}
