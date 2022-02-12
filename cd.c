/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:47:28 by abittel           #+#    #+#             */
/*   Updated: 2022/02/12 20:03:19 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "build_in.h"
#include "env_manager.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int	is_absolute_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	return (0);
}

int	idx_end_word(char *str, int i)
{
	while (str[++i])
		if (str[i] == '/')
			return (i - 1);
	return (i - 1);
}

void	add_file_in_path(char **str, char *add)
{
	char	*inter;
	int		size;

	size = ft_strlen(*str);
	if ((*str)[size - 1] != '/')
	{
		inter = *str;
		*str = ft_strjoin(*str, "/");
		free(inter);
	}
	inter = *str;
	*str = ft_strjoin(*str, add);
	free(inter);
	free(add);
}

void	delete_file_in_path(char **str)
{
	int		i;
	char	*inter;

	i = ft_strlen(*str);
	while (--i > 0)
		if ((*str)[i] == '/')
			break ;
	if (i == 0)
		inter = ft_strdup("/");
	else
		inter = ft_substrdup(*str, 0, i - 1);
	if (*str)
		free (*str);
	*str = inter;
}

char	*get_absolute_path(t_list *env, char *path)
{
	int		i;
	char	*res;
	char	*inter_w;
	char	*path_c;

	i = -1;
	res = ft_strdup(get_val_var(env, "PWD"));
	path_c = path;
	while (path_c[++i])
	{
		if (path_c[i] != '/')
		{
			inter_w = ft_substrdup(path, i, idx_end_word(path_c, i));
			if (!ft_strcmp(inter_w, ".."))
				delete_file_in_path(&res);
			else if (ft_strcmp(inter_w, "."))
				add_file_in_path(&res, inter_w);
			i = idx_end_word(path_c, i);
		}
	}
	return (res);
}

void	cd_bi(t_list *env, char **cmd)
{
	DIR				*folder;
	int				size;
	char			*path;
	char			**inter;

	size = size_tabstr(cmd);
	if (size > 2 || size < 2)
		return ;
	inter = ft_split(cmd[1], ' ');
	if (size_tabstr(inter) > 1)
	{
		ft_putstr_fd("cd: Too mutch argument", 2);
		free_tabstr(inter);
		return ;
	}
	free_tabstr(inter);
	path = ft_strdup(cmd[1]);
	if (!is_absolute_path(cmd[1]))
	{
		free (path);
		path = get_absolute_path(env, cmd[1]);
	}
	folder = opendir(path);
	if (folder)
	{
		add_val(env, "OLDPWD", get_val_var(env, "PWD")); 
		add_val(env, "PWD", path); 
	}
	else
		perror("BISCUIT:cd");
	closedir(folder);
	free (path);
}
