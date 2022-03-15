/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:09:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 17:17:59 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "build_in.h"
#include "exec_cmd.h"
#include <unistd.h>

int	env_bi(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "?=", 2))
		{
			ft_putstr_fd(env[i], fd);
			write (fd, "\n", 1);
		}
	}
	return (0);
}

void	print_var_export(t_list *inter, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(((t_env_var *)inter->content)->name, fd);
	if (!((t_env_var *)inter->content)->is_export)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(((t_env_var *)inter->content)->value, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}

void	env_export(t_list *lst, int fd)
{
	t_list	*inter;

	inter = lst;
	while (inter && inter->next)
	{
		if (ft_strncmp(((t_env_var *)inter->content)->name, "?", 2))
			print_var_export(inter, fd);
		inter = inter->next;
	}
	if (ft_strncmp(((t_env_var *)inter->content)->name, "?", 2))
		print_var_export(inter, fd);
}
