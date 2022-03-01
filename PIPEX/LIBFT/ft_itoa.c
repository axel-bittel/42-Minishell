/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:08:59 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:24:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	count;
	int	tmp;

	count = 1;
	tmp = n;
	if (n < 0)
	{
		tmp = -n;
		count++;
	}
	while (tmp >= 10)
	{
		tmp = (tmp / 10);
		count++;
	}
	return (count);
}

static char	*int_max_or_min(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
		return (ft_strdup("2147483647"));
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	if (n == -2147483648 || n == 2147483647)
		return (int_max_or_min(n));
	res = malloc(sizeof(char) * (intlen(n) + 1));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	i = intlen(n);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[i] = '\0';
	i--;
	while (n > 0)
	{
		res[i] = (n % 10) + 48;
		i--;
		n = (n / 10);
	}
	return (res);
}
