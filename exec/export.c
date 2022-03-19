/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:21:21 by abittel           #+#    #+#             */
/*   Updated: 2022/03/19 23:23:02 by abittel          ###   ########.fr       */
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

int	export_bi(char **cmd, t_list *env, int fd, int **tok)
{
	int	i;
	int	j;
	char	*name;
	char	*val;

	i = 0;
	(void)fd;
	if (blanck_tabcmd(cmd + 1))
		env_export(env, fd);
	else
	{
		while (i < size_tabstr(cmd) && cmd[++i])
		{
			j = -1;
			while (cmd[i] && cmd[i][++j])
			{
				if (ft_isalpha(cmd[i][j]) && cmd[i][j] != '=')
				{
					name = get_name(cmd, &i, &j);
					if (cmd[i] && cmd[i][++j] == '=')
					{
						val = get_val(cmd, &i, &j);
						add_val(env, name, val, 0);
					}
					else if(ft_isalpha(name[0]))
						add_val(env, name, " ", 1);
					else
						print_error();
				}
				else
				{
					print_error();
					return (1);
				}
			}
		}
	}
	return (0);
}
