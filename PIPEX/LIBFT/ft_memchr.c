/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:10:45 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:25:25 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	to_find;
	unsigned char	*str;

	i = 0;
	to_find = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == to_find)
			return (str + i);
		i++;
	}
	return (NULL);
}
