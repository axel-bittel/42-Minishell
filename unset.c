/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:24:42 by abittel           #+#    #+#             */
/*   Updated: 2022/03/03 17:40:49 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "build_in.h"
#include "env_manager.h"

int	unset_bi(char **cmd, t_list *env)
{
	int		i;
	char	*inter;

	i = 0;
	while (cmd[++i])
	{
		inter = get_val_var(env, cmd[i]);
		if (*inter)
			delete_val(&env, cmd[i]);
		else
			free(inter);
	}
	return (0);
}
