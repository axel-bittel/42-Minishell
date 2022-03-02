/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:11:01 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:25:54 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destt;
	unsigned char	*srcc;

	if (!dest && !src)
		return (dest);
	destt = (unsigned char *)dest;
	srcc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		destt[i] = srcc[i];
		i++;
	}
	return (dest);
}
