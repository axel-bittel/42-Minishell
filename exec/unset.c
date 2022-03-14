/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:24:42 by abittel           #+#    #+#             */
/*   Updated: 2022/03/14 18:59:39 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "build_in.h"
#include "exec_cmd.h"

int	unset_bi(char **cmd, t_list *env)
{
	int		i;
	char	*inter;

	i = 0;
	while (cmd[++i])
	{
		inter = get_val_var(env, cmd[i]);
		delete_val(&env, cmd[i]);
	}
	return (0);
}
