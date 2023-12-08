/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.small.f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:38:07 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 13:38:40 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

void	fill_result(char *result, char *new_value, char *del, size_t **m)
{
	size_t	*i;
	size_t	*j;

	i = m[0];
	j = m[1];
	strcpy(result + *j, new_value);
	*j += ft_strlen(new_value);
	*i += ft_strlen(del) + 1;
}
