#include "minishell.h"

void print_export_char(char *str, bool _print_new_line)
{
	int i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			printf("\\n");
			if (str[i + 1] != '\0')
				i++;
		}
		else
			printf("%c", str[i]);
		i++;
	}
	if (_print_new_line)
		printf("\"\n");
}

int check_repetition(t_env *new, t_env **env)
{
	t_env *temp;
	int i;

	temp = *env;
	i = 0;
	if (new->vars[0][0] == '=')
	{
		printf("minishell: %s is not a valid identifier\n", new->vars[0]);
		return (1);
	}
	while (temp)
	{
		if (ft_strcmp(temp->vars[0], new->vars[0]) == 0)
		{
			if (temp->vars[1] == NULL)
				temp->vars[1] = (char *)malloc(ft_strlen(new->vars[1]) * sizeof(char));
			ft_strlcpy(temp->vars[1], new->vars[1], strlen(temp->vars[1]));
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

void print_export_env(t_cmds *node)
{
	t_env *env;

	env = node->sh->env;
	while (env)
	{
		printf("declare -x ");
		print_export_char(env->vars[0], false);
		if (env->vars[1])
		{
			printf("=\"");
			print_export_char(env->vars[1], true);
		}
		env = env->next;
	}
	return;
}

int compareStrings(const char *str1, const char *str2)
{
	return (strcmp(str1, str2));
}

void swapNodes(t_env *a, t_env *b)
{
	char **temp;

	temp = a->vars;
	a->vars = b->vars;
	b->vars = temp;
}

void list_order(t_env *node)
{
	int swapped;
	t_env *ptr1;
	t_env *lptr;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = node;
		lptr = NULL;
		while (ptr1->next != lptr)
		{
			if (compareStrings(ptr1->vars[0], ptr1->next->vars[0]) > 0)
			{
				swapNodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

int ft_export(t_cmds *node)
{
	int i;
	t_env *new;
	int *dups;

	dups = NULL;
	i = 1;
	redirect(node);
	dups = set_dups(node);
	if (!node->args[i])
	{
		print_export_env(node);
		close_redi(node);
		if (dups[0] != -10)
			close(dups[0]);
		if (dups[1] != -10)
			close(dups[1]);
		return (1);
	}
	while (node->args[i])
	{
		new = ft_env_add(ft_strdup(node->args[i]));
		if (check_repetition(new, &node->sh->env) == 0)
			ft_ml_envadd_back(&node->sh->env, new);
		else
			ft_env_delete(&new);
		i++;
	}
	list_order(node->sh->env);
	if (dups[0] != -10)
		close(dups[0]);
	if (dups[1] != -10)
		close(dups[1]);
	if (node->next || node->prev)
		clean(node->sh, true, 0, NULL);
	free(dups);
	return (1);
}