/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:38 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 21:34:04 by abittel          ###   ########.fr       */
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

void	add_val(t_list *lst, char *name, char *val)
{
	char	*res;
	t_list	*inter;

	inter = lst;
	res = get_val_var(lst, name);
	if (!res[0])
		add_val_not_exist(lst, name, val, res);
	else
	{
		while (inter->next)
		{
			if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
			{
				free(((t_env_var *)inter->content)->value);
				((t_env_var *)inter->content)->value = ft_strdup(val);
			}
			inter = inter->next;
		}
		if (!ft_strcmp(name, ((t_env_var *)inter->content)->name))
		{
			free(((t_env_var *)inter->content)->value);
			((t_env_var *)inter->content)->value = ft_strdup(val);
		}
	}
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

char	**get_env_in_char(t_list *env)
{
	int		i;
	t_list	*inter_l;
	char	**res;
	char	*inter;

	i = -1;
	if (!env)
		return (0);
	res = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	inter_l = env;
	while (inter_l->next)
	{
		res[++i] = ft_strjoin (((t_env_var *)inter_l->content)->name, "=");
		inter = res[i];
		res[i] = ft_strjoin (res[i], ((t_env_var *)inter_l->content)->value);
		free(inter);
		inter_l = (t_list *)inter_l->next;
	}
	res[++i] = ft_strjoin(((t_env_var *)inter_l->content)->name, "=");
	inter = res[i];
	res[i] = ft_strjoin(res[i], ((t_env_var *)inter_l->content)->value);
	free(inter);
	res[++i] = NULL;
	return (res);
}
