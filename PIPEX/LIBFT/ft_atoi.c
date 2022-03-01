/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:06:47 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 12:00:04 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	int_max_or_min(const char *str)
{
	if (ft_strcmp(str, "-2147483648") == 0)
		return (INT_MIN);
	else if (ft_strcmp(str, "2147483647") == 0)
		return (INT_MAX);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	if ((ft_strcmp(str, "-2147483648") == 0) \
			|| (ft_strcmp(str, "2147483647") == 0))
		return (int_max_or_min(str));
	while (str[i] && ((str[i] > 8 && str[i] < 14) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
