/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 01:04:25 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 01:06:25 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniBuiltins.h>

void	swpnodes(t_env *a, t_env *b){
	char **temp;

	temp = a->vars;
	a->vars = b->vars;
	b->vars = temp;
}

void	print_export_char(char *str, bool _print_new_line){
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return ;
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