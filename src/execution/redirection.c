/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                 +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:38:59 by pedro             #+#    #+#             */
/*   Updated: 2023/10/01 10:52:57 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type red_type_checker(char *str)
{
	t_type final;

	final = FILE_NONE;
	if (str[0] == INFILE)
		final = FILE_IN_READ + (str[1] == INFILE);
	if (str[0] == OUTTRUC)
		final = 3 + (str[1] == OUTTRUC);
	return (final);
}

t_redirections *redi_new(int *i, t_cmds *cm, t_type type)
{
	t_redirections *new;

	printf("%s%s%s\n", RED, __func__, RESET);
	new = malloc(sizeof(t_redirections));
	if (!new)
		return NULL;
	new->element = malloc(sizeof(char *) * 3);
	if (!new->element)
	{
		free(new);
		return NULL;
	}
	new->element[0] = ft_strdup(cm->args[*i]);
	split_str_del(cm->args, *i);
	new->element[1] = ft_strdup(cm->args[*i]);
	split_str_del(cm->args, *i);
	new->element[2] = NULL;
	new->mode = type;
	new->next = NULL;
	print_split(new->element);
	return new;
}

void redirection_analizer(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	if (redi_node == FILE_NONE)
	{
		printf("There is no redirection.\n");
		return;
	}
	printf("%s%s%s\n", YEL, __func__, RESET);
	printf("String Selector: \n");
	print_special(node->args[*i]);
	t_redirections *new;
	(void)sh;
	new = redi_new(i, node, redi_node);
}

void redirection(t_cmds *node, t_shell *sh)
{
	char **args;
	t_type red_mode;
	int i;

	red_mode = FILE_NONE;
	i = 0;
	args = node->args;
	int loop = -1;
	while (args[i])
	{
		remove_quotes(args[i]);
		red_mode = red_type_checker(args[i]);
		redirection_analizer(red_mode, node, &i, sh);
		print_split(args);
		if (red_mode == FILE_NONE)
			i++;
		if (loop == 100)
			break;
		loop++;
	}
	clean(sh, true, 0, "STOP HERE\n");
}
