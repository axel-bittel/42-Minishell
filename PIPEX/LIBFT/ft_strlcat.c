/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:13:26 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/19 17:14:14 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	to_append;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	to_append = size - dst_len - 1;
	i = 0;
	j = 0;
	if ((size == 0) || (size <= dst_len))
		return (size + ft_strlen(src));
	while (dst[i])
		i++;
	while ((j < to_append) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return ((size_t)(dst_len + ft_strlen(src)));
}

/* int main()
{
	char dest[30];
	memset(dest, 0, 30);
	char *src = (char *)"AAAAAAAAA";
	memset(dest, 'C', 5);
	ft_strlcat(dest, src, -1);
	printf("%s", dest);
} */
