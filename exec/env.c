/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:09:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/17 18:03:28 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "build_in.h"
#include "exec_cmd.h"
#include <unistd.h>

int	env_bi(t_list *lst, int fd)
{
	t_list	*inter;

	inter = lst;
	while (inter && inter->next)
	{
		if (ft_strncmp(((t_env_var *)inter->content)->name, "?", 2) &&\
!((t_env_var *)inter->content)->is_export)
		{
			ft_putstr_fd(((t_env_var *)inter->content)->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(((t_env_var *)inter->content)->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		inter = inter->next;
	}
	if (ft_strncmp(((t_env_var *)inter->content)->name, "?", 2) && \
!((t_env_var *)inter->content)->is_export)
	{
		ft_putstr_fd(((t_env_var *)inter->content)->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(((t_env_var *)inter->content)->value, fd);
		ft_putstr_fd("\n", fd);
	}
	return (1);
}

void	print_var_export(t_list *inter, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(((t_env_var *)inter->content)->name, fd);
	if (!((t_env_var *)inter->content)->is_export)
	{
		ft_putstr_fd("=", fd);
		ft_putstr_fd(((t_env_var *)inter->content)->value, fd);
		ft_putstr_fd("\n", fd);
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
