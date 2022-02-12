/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:17:00 by abittel           #+#    #+#             */
/*   Updated: 2021/07/25 23:35:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include <unistd.h>

static int	ft_putnbr_rec(int n, int fd)
{
	char	res;

	if (!n)
		return (0);
	else
	{
		res = n - ft_putnbr_rec(n / 10, fd) * 10 + 48;
		write(fd, &res, 1);
		return (n);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	is_neg;

	if (fd < 0)
		return ;
	if (n == INT_MIN)
		write (fd, "-2147483648", 11);
	else if (n == 0)
		write (fd, "0", 1);
	else
	{
		is_neg = 1;
		if (n < 0)
		{
			is_neg = -1;
			write (fd, "-", 1);
		}
		ft_putnbr_rec(n * is_neg, fd);
	}
}
