/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:39:25 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 22:34:46 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include "libft.h"

static int	is_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n' || \
c == '\f' || c == ' ')
		return (1);
	return (0);
}

static int	can_add(long long num, char c, int is_neg)
{
	long long	res;

	res = num;
	res = res * 10 + c - 48;
	if (res < num && is_neg == 1)
		return (-1);
	else if (res < num && is_neg == -1)
		return (0);
	else
		return (1);
}

static unsigned long long	ft_atoi_logic(char *nprt)
{
	int			i;
	int			is_neg;
	long long	res;

	i = 0;
	is_neg = 1;
	res = 0;
	if (!nprt)
		return (0);
	if (nprt[0] == '-')
	{
		is_neg = -1;
		i = 1;
	}
	while (nprt[i])
	{
		if (ft_isdigit(nprt[i]) && can_add(res, nprt[i], is_neg) == 1)
			res = res * 10 + nprt[i] - 48;
		else if (ft_isdigit(nprt[i]) && can_add(res, nprt[i], is_neg) != 1)
			return (can_add(res, nprt[i], is_neg));
		else if (nprt[i] != '+' || (nprt[i] == '+' && i > 0))
			return (res * is_neg);
		i = i + 1;
	}
	return (res * is_neg);
}

long long	ft_atoi(const char *nprt)
{
	long long	res;
	int			i;

	if (!ft_strcmp((char *)nprt, "-2147483648"))
		return (-2147483648);
	else
	{
		i = 0;
		while (is_space(nprt[i]))
			i += 1;
		res = ft_atoi_logic((char *)nprt + i);
		if (res == LLONG_MIN)
			return (0);
		return ((long long)res);
	}
}
