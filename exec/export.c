/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:21:21 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 17:10:27 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "libft.h"
#include "build_in.h"
#include "utils.h"
#include "exec_cmd.h"

void	print_error(char **cmd)
{
	ft_putstr_fd("BISCUIT:export ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" :not a valid identifier\n", 2);
}

int	check_export_error(char **cmd, t_list *env, int fd)
{
	int		size;
	char	**env_chr;

	size = size_tabstr(cmd);
	env_chr = get_env_in_char(env);
	if (size > 2)
	{
		ft_putstr_fd("BISCUIT:export:arguments error\n", 2);
		return (free_tabstr(env_chr), 1);
	}
	else if (size == 1)
		env_bi(env_chr, fd);
	free_tabstr(env_chr);
	return (0);
}

int	add_var(char **cmd, int *i, int j, t_list *env)
{
	char	*name;
	char	*data;

	data = 0;
	name = ft_substrdup(cmd[*i], get_deb_word(cmd[*i], j), j - 1);
	if (cmd[*i][j + 1])
		data = ft_substrdup(cmd[*i], j + 1, get_end_word(cmd[*i], j + 1));
	else if (cmd[*i + 1])
	{
		data = ft_strdup(cmd[*i + 1]);
		(*i)++;
	}
	if (!ft_isalpha(name[0]))
		return (print_error(cmd), free(name), free(data), 1);
	else
		add_val(env, name, data, 1);
	free(name);
	if (data)
		free(data);
	return (0);
}

int	export_bi(char **cmd, t_list *env, int fd)
{
	int	i;
	int	j;

	i = 0;
	(void)fd;
	if (blanck_tabcmd(cmd + 1))
		env_export(env, fd);
	else while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '=')
				if (add_var(cmd, &i, j, env))
					return (1);
		}
	}
	return (0);
}
