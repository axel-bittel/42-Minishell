/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:11:19 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:11:20 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*source;

	i = 0;
	dest = (char *)dst;
	source = (char *)src;
	if (dest > source)
	{
		while (i < len)
		{
			dest[len - i - 1] = source[len - i - 1];
			i++;
		}
	}
	else if (source > dest)
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dst);
}
