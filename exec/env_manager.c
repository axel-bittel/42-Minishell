/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:38 by abittel           #+#    #+#             */
/*   Updated: 2022/03/20 00:40:20 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "exec_cmd.h"
#include "parsing.h"

t_list	*get_fst_env(char **envp, char *lunch)
{
	int			i;
	char		**line_splt;
	t_list		*res;
	t_env_var	*inter;

	res = 0;
	i = -1;
	while (envp && envp[++i])
	{
		line_splt = ft_split(envp[i], '=');
		inter = malloc(sizeof(t_env_var));
		inter->name = ft_strdup(line_splt[0]);
		inter->value = ft_tabstrjoin(line_splt + 1);
		inter->is_export = 0;
		if (res)
			ft_lstadd_back(&res, ft_lstnew((void *)inter));
		else
			res = ft_lstnew((void *)inter);
		free_tabstr(line_splt);
	}
	if (!envp[0])
		create_base_env(&res, lunch);
	return (res);
}

char	*get_val_var(t_list *lst, char *name)
{
	char	*res_null;
	t_list	*inter;

	inter = lst;
	while (inter && inter->next)
	{
		if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
			return (((t_env_var *)inter->content)->value);
		inter = inter->next;
	}
	if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
		return (((t_env_var *)inter->content)->value);
	res_null = malloc (sizeof(char));
	*res_null = 0;
	return (res_null);
}

int	delete_val(t_list **lst, char *name)
{
	t_list	*inter;
	t_list	*prec;

	prec = 0;
	inter = *lst;
	while (inter && lst && inter->next)
	{
		if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
		{
			delete_elem(lst, inter, prec);
			return (1);
		}
		prec = inter;
		inter = inter->next;
	}
	if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
	{
		prec->next = NULL;
		free_env_var((t_env_var *)inter->content);
		free(inter);
	}
	return (1);
}
