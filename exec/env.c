/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:09:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/03 16:11:43 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "build_in.h"
#include <unistd.h>

int	env_bi(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "?=", 2))
		{
			ft_putstr_fd(env[i], fd);
			write (fd, "\n", 1);
		}
	}
	return (1);
}
