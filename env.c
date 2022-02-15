/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:09:32 by abittel           #+#    #+#             */
/*   Updated: 2022/02/15 10:13:23 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "build_in.h"
#include <unistd.h>

int	env_bi(char **env)
{
	int	i;

	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
		write (1, "\n", 1);
	}
	return (1);
}
