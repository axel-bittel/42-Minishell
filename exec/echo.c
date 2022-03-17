/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:47:53 by abittel           #+#    #+#             */
/*   Updated: 2022/03/17 17:50:40 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

int	is_arg_n(char *cmd)
{
	int	i;

	i = -1;
	if(!cmd || cmd[++i] != '-')
		return (0);
	while (cmd && cmd[++i])
		if (cmd[i] != 'n' && cmd[i] != ' ')
			return (0);
	return (1);
}

int	echo_bi(char **cmd, int fd)
{
	int		i;
	int		end_line;
	int		find_arg;
	char	*inter;

	i = 0;
	end_line = 1;
	find_arg = 0;
	while (cmd[++i])
	{
		inter = ft_strdup(cmd[i]);
		if (is_arg_n(cmd[i]) && !find_arg)
			end_line = 0;
		else
		{
			ft_putstr_fd(inter, fd);
			find_arg = 1;
		}
		//if(cmd[i][0] == '-')
			//write (fd, " ", 1); 
		free(inter);
	}
	if (end_line)
		write(fd, "\n", 1);
	return (0);
}
