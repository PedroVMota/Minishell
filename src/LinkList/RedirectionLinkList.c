
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

void redi_checker(char ***new, t_shell *sh)
{
	int i;
	i = -1;
	while ((*new)[0][++i])
	{
		if ((*new)[0][i] == '\7' || (*new)[0][i] == '\6' || (*new)[0][i] == '\b')
			continue;
		else
			break;
	}
	(*new)[1] = ft_strdup(&(*new)[0][i]);
	if (!(*new)[1])
		clean(sh, true, 1, "Malloc Error\n");
}

t_redirections *redi_new(int *i, t_cmds *cm, t_type type)
{
	t_redirections *new;

	new = malloc(sizeof(t_redirections));
	if (!new)
		return (NULL);
	new->element = malloc(sizeof(char *) * 3);
	if (!new->element)
	{
		free(new);
		return (NULL);
	}
	
	new->mode = type;
	new->element[0] = ft_strdup(cm->args[*i]);
	split_str_del(cm->args, *i);
	if (!cm->args[*i])
		redi_checker(&new->element, cm->sh);
	else
	{
		new->element[1] = ft_strdup(cm->args[*i]);
		split_str_del(cm->args, *i);
	}
	info(new->element[0], GRN);
	info(new->element[1], GRN);
	new->element[2] = NULL;
	new->next = NULL;

	return (new);
}

t_redirections *redirection_last_ptr(t_redirections *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void redirection_in(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	t_redirections *new;
	t_redirections *last;

	(void)sh;
	if (redi_node == FILE_NONE)
		return;
	new = redi_new(i, node, redi_node);
	if (!new)
		return;
	if (!node->infiles)
	{
		node->infiles = new;
		return;
	}
	last = redirection_last_ptr(node->infiles);
	last->next = new;
}

void redirection_out(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	t_redirections *new;
	t_redirections *last;

	(void)sh;
	if (redi_node == FILE_NONE)
		return;
	new = redi_new(i, node, redi_node);
	if (!new)
		return;
	if (!node->outfile)
	{
		node->outfile = new;
		return;
	}
	last = redirection_last_ptr(node->outfile);
	last->next = new;
}

void placer(t_type redi_node, t_cmds *node, int *i, t_shell *sh)
{
	if (redi_node == FILE_IN_HEREDOC || redi_node == FILE_IN_READ)
		redirection_in(redi_node, node, i, sh);
	if (redi_node == FILE_OUT_TRUNC || redi_node == FILE_OUT_APPEND)
		redirection_out(redi_node, node, i, sh);
}

void redirection(t_cmds *node, t_shell *sh)
{
	char **args;
	t_type red_mode;
	int i;
	int loop;

	red_mode = FILE_NONE;
	i = 0;
	args = node->args;
	loop = -1;
	while (args[i])
	{
		remove_quotes(args[i]);
		red_mode = red_type_checker(args[i]);
		placer(red_mode, node, &i, sh);
		if (red_mode == FILE_NONE)
			i++;
		loop++;
	}
	if (!node->args[0])
	{
		free(node->args);
		node->args = NULL;
	}
}
