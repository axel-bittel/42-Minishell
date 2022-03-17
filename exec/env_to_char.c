/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:58:48 by abittel           #+#    #+#             */
/*   Updated: 2022/03/17 20:05:22 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "exec_cmd.h"
#include "parsing.h"

void	join_tab(char **res, t_list *inter_l, int i)
{
	char	*inter;

	res[i] = ft_strjoin (((t_env_var *)inter_l->content)->name, "=");
	inter = res[i];
	res[i] = ft_strjoin(res[i], ((t_env_var *)inter_l->content)->value);
	free(inter);
}

char	**get_env_in_char(t_list *env)
{
	int		i;
	t_list	*inter_l;
	char	**res;

	i = -1;
	if (!env)
		return (0);
	res = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	inter_l = env;
	while (inter_l->next)
	{
		if (!(((t_env_var *)inter_l->content)->is_export))
		{
			i++;
			join_tab(res, inter_l, i);
		}
		inter_l = (t_list *)inter_l->next;
	}
	i++;
	join_tab(res, inter_l, i);
	res[++i] = NULL;
	return (res);
}
