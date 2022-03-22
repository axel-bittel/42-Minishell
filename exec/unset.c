/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:24:42 by abittel           #+#    #+#             */
/*   Updated: 2022/03/22 22:49:11 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_in.h"
#include "exec_cmd.h"

int	unset_bi(char **cmd, t_list *env)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (ft_isalpha(cmd[i][0]))
			delete_val(&env, cmd[i]);
		else
		{
			ft_putstr_fd("minishell:unset:ARG ERROR\n", 2);
			return (1);
		}
	}
	return (0);
}
