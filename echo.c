/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:47:53 by abittel           #+#    #+#             */
/*   Updated: 2022/02/21 16:18:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

int	echo_bi(char **cmd)
{
	int		i;
	int		end_line;
	char	*inter;

	i = 0;
	end_line = 1;
	while (cmd[++i])
	{
		inter = cmd[i];
		if (!ft_strcmp(cmd[i], "-n") && i == 1)
			end_line = 0;
		else
			ft_putstr_fd(inter, 1);
		if (cmd[i + 1])
			write(1, "", 1);
		free(inter);
	}
	if (end_line)
		write(1, "\n", 1);
	return (0);
}
