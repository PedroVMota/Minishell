/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:03:25 by pvital-m          #+#    #+#             */
/*   Updated: 2023/03/10 22:59:45 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long long	i;
	char		*d_dst;
	char		*s_src;

	i = 0;
	d_dst = (char *)dst;
	s_src = (char *)src;
	if (d_dst == s_src)
		return (dst);
	if (d_dst > s_src)
	{
		while (len--)
			d_dst[len] = s_src[len];
	}
	else
	{
		while (i < len)
		{
			d_dst[i] = s_src[i];
			i++;
		}
	}
	return (dst);
}
