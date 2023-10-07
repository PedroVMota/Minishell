/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:41:49 by pvital-m          #+#    #+#             */
/*   Updated: 2023/02/26 22:49:55 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**Applies the function f to each character of the string passed as argument by
**giving its index as first argument to create a
**“fresh” new string (with malloc(3)) resulting from the successive
**applications of f.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*result;
	unsigned int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		result[i] = f(i, *s);
		i++;
		s++;
	}
	result[i] = '\0';
	return (result);
}
