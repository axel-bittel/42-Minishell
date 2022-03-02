/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:13:16 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/19 15:20:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*res;
// 	int		total_length;
// 	int		i;
// 	int		j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	total_length = ft_strlen(s1) + ft_strlen(s2);
// 	res = malloc((sizeof(char) * total_length) + 1);
// 	i = -1;
// 	j = 0;
// 	if (!res)
// 		return (NULL);
// 	while (s1[++i])
// 		res[i] = s1[i];
// 	while (s2[j])
// 	{
// 		res[i] = s2[j];
// 		j++;
// 		i++;
// 	}
// 	res[i] = 0;
// 	return (res);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
