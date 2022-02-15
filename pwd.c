/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:59:04 by abittel           #+#    #+#             */
/*   Updated: 2022/02/14 23:40:21 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "env_manager.h"
#include <unistd.h>

int	pwd_bi(t_list *env)
{
	ft_putstr_fd(get_val_var(env, "PWD"), 1);
	write(1, "\n", 1);
	return (1);
}
