/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:40:10 by abittel           #+#    #+#             */
/*   Updated: 2022/03/20 00:44:08 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "exec_cmd.h"

void	make_changes(t_list *inter, char *val, int is_export)
{
	free(((t_env_var *)inter->content)->value);
	((t_env_var *)inter->content)->value = ft_strdup(val);
	((t_env_var *)inter->content)->is_export = is_export;
}

void	add_val(t_list *lst, char *name, char *val, int is_export)
{
	char	*res;
	t_list	*inter;

	inter = lst;
	res = get_val_var(lst, name);
	if (!res[0])
		(free(res), add_val_not_exist(lst, name, val, is_export));
	else if (!is_export)
	{
		while (inter->next)
		{
			if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
				make_changes(inter, val, is_export);
			inter = inter->next;
		}
		if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
			make_changes(inter, val, is_export);
	}
}
