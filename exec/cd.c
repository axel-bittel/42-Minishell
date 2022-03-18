/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:47:28 by abittel           #+#    #+#             */
/*   Updated: 2022/03/18 11:41:03 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "build_in.h"
#include "exec_cmd.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int	go_home(t_list *env)
{
	char	*home;

	home = get_val_var(env, "HOME");
	if (!home[0])
	{
		free (home);
		ft_putstr_fd("minishell:cd: HOME not declared\n", 2);
		return (1);
	}
	chdir(home);
	add_val(env, "OLDPWD", get_val_var(env, "PWD"), 0);
	add_val(env, "PWD", home, 0);
	return (0);
}

int	is_error(char **cmd)
{
	char	**inter;
	char	*inter_free;

	if (size_tabstr(cmd) == 1)
		return (0);
	inter_free = ft_tabstrjoin(cmd + 1);
	inter = ft_split(inter_free, ' ');
	free(inter_free);
	if (size_tabstr(inter) > 1)
	{
		ft_putstr_fd("minishell:cd: Too mutch argument\n", 2);
		free_tabstr(inter);
		return (1);
	}
	free_tabstr(inter);
	return (0);
}

void	get_path(t_list *env, char **cmd, char **path)
{
	char	*inter_free;

	inter_free = ft_tabstrjoin(cmd + 1);
	*path = ft_strtrim(inter_free, " ");
	free(inter_free);
	if (!is_absolute_path(cmd[1]))
	{
		free (*path);
		*path = get_absolute_path(env, cmd[1]);
	}
}

int	cd_bi(t_list *env, char **cmd)
{
	DIR		*folder;
	char	*path;
	int		res;

	if (is_error(cmd))
		return (1);
	if (size_tabstr(cmd) == 1)
		return (go_home(env));
	get_path(env, cmd, &path);
	folder = opendir(path);
	res = 1;
	if (folder)
	{
		chdir(path);
		add_val(env, "OLDPWD", get_val_var(env, "PWD"), 0);
		add_val(env, "PWD", path, 0);
		res = 0;
	}
	else
		perror("BISCUIT:cd");
	closedir(folder);
	free (path);
	return (res);
}
