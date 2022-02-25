/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:59:04 by abittel           #+#    #+#             */
/*   Updated: 2022/02/25 20:24:46 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "env_manager.h"
#include <unistd.h>

int	pwd_bi(t_list *env, int fd)
{
	ft_putstr_fd(get_val_var(env, "PWD"), 1);
	write(1, "\n", fd);
	return (0);
}
