/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:21:11 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/19 21:31:57 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char const c, char const *set)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		tab[2];
	int		start;
	char	*res;

	tab[0] = 0;
	tab[1] = 0;
	if (!s || !set)
		return (NULL);
	while (s[tab[0]] && (char_in_set(s[tab[0]], set) == 1))
		tab[0]++;
	if (!s[tab[0]])
		return (ft_strdup(""));
	start = tab[0];
	tab[0] = (ft_strlen(s) - 1);
	while (s[tab[0]] && char_in_set(s[tab[0]], set))
		tab[0]--;
	res = malloc(sizeof(char) * (tab[0] - start + 2));
	if (!res)
		return (NULL);
	while (start <= tab[0])
		res[tab[1]++] = s[start++];
	res[tab[1]] = '\0';
	return (res);
}
