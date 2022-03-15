/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:24:42 by abittel           #+#    #+#             */
/*   Updated: 2022/03/14 22:39:59 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "build_in.h"
#include "exec_cmd.h"

int	unset_bi(char **cmd, t_list *env)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		delete_val(&env, cmd[i]);
	}
	return (0);
}
