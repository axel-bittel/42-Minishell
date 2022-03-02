/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:39:40 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/16 22:45:08 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

int	ft_new_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (n + 2));
	if (!str || !res)
		return (NULL);
	while ((i <= n) && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_new_strjoin(char *s1, char *s2)
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

// char	*ft_strdup(char *s)
// {
// 	char	*res;
// 	int		i;
// 	int		len_s;

// 	i = 0;
// 	len_s = ft_strlen(s);
// 	res = malloc(sizeof(char) * (len_s + 1));
// 	if (!res || !s)
// 		return (0);
// 	while (s[i])
// 	{
// 		res[i] = s[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }
