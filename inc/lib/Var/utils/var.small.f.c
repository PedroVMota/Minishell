/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.small.f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:38:07 by pedro             #+#    #+#             */
/*   Updated: 2023/12/08 13:42:15 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"

void	fill_result(char *result, char *new_value, char *del, size_t **m)
{
	size_t	*i;
	size_t	*j;

	i = m[0];
	j = m[1];
	ft_strlcpy(result + *j, new_value, ft_strlen(new_value) + 1);
	*j += ft_strlen(new_value);
	*i += ft_strlen(del) + 1;
}
