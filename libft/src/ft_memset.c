/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:57:02 by pvital-m          #+#    #+#             */
/*   Updated: 2023/02/23 12:49:20 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*p++ = value;
		i++;
	}
	return (b);
}
