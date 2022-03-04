/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:59:04 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 19:49:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "exec_cmd.h"
#include <unistd.h>

int	pwd_bi(t_list *env, int fd)
{
	ft_putstr_fd(get_val_var(env, "PWD"), fd);
	write(fd, "\n", 1);
	return (0);
}
