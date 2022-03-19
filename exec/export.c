/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:21:21 by abittel           #+#    #+#             */
/*   Updated: 2022/03/20 00:35:12 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "libft.h"
#include "build_in.h"
#include "utils.h"
#include "exec_cmd.h"

void	print_error(void)
{
	ft_putstr_fd("BISCUIT:export ", 2);
	ft_putstr_fd(" :ARG ERROR\n", 2);
}

int	export_boucle(t_sub_cmd *cmd, int *i, int *j, t_list *env)
{
	char	*name;
	char	*val;

	if (ft_isalpha(cmd->cmd[*i][*j]) && cmd->cmd[*i][*j] != '=')
	{
		name = get_name(cmd, i, j);
		if (cmd->cmd[*i] && cmd->cmd[*i][++(*j)] == '=')
		{
			val = get_val(cmd, i, j);
			add_val(env, name, val, 0);
			free(val);
		}
		else if (ft_isalpha(name[0]))
			add_val(env, name, " ", 1);
		else
			print_error();
		free(name);
	}
	else
	{
		print_error();
		return (1);
	}
	return (0);
}

int	export_bi(t_sub_cmd *cmd, t_list *env, int fd)
{
	int	i;
	int	j;

	i = 0;
	(void)fd;
	if (blanck_tabcmd(cmd->cmd + 1))
		env_export(env, fd);
	else
	{
		while (i < size_tabstr(cmd->cmd) && cmd->cmd[++i])
		{
			j = -1;
			while (cmd->cmd[i] && cmd->cmd[i][++j])
				if (export_boucle(cmd, &i, &j, env))
					return (1);
		}
	}
	return (0);
}
