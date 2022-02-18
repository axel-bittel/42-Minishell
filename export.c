/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:21:21 by abittel           #+#    #+#             */
/*   Updated: 2022/02/17 18:15:19 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "env_manager.h"
#include "libft.h"
#include "build_in.h"

char	get_deb_word(char *str, int i)
{
	while (i >= 0 && str[i] != ' ')
		i--;
	return (i + 1);
}

void	print_error(char **cmd)
{
	ft_putstr_fd("BISCUIT:export", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(":not a valid identifier", 2);
}

int	check_export_error(char **cmd, t_list *env)
{
	int		size;
	char	**env_chr;

	size = size_tabstr(cmd);
	env_chr = get_env_in_char(env);
	if (size > 2)
	{
		ft_putstr_fd("BISCUIT:export:arguments error", 2);
		return (free_tabstr(env_chr), 1);
	}
	else if (size == 1)
		env_bi(env_chr);
	free_tabstr(env_chr);
	return (0);
}

int	export_bi(char **cmd, t_list *env)
{
	int	i;
	char	*name;
	char	*data;

	i = -1;
	if(check_export_error(cmd, env))
		return (1);
	while (cmd[1] && cmd[1][++i])
	{
		if (cmd[1][i] == '=')
		{
			name = ft_substrdup(cmd[1], get_deb_word(cmd[1], i), i - 1);
			data = ft_substrdup(cmd[1], i + 1, ft_strlen(cmd[1]) - 1);
			if (!ft_isalpha(name[0]))
				return (print_error(cmd), free(name), free(data), 1);
			else
				add_val(env, name, data);
			free(name);
			free(data);
			break;
		}
	}
	return (0);
}
