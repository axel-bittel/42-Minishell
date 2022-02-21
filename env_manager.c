/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:38 by abittel           #+#    #+#             */
/*   Updated: 2022/02/21 16:22:22 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "env_manager.h"
#include "parsing.h"


t_list	*get_fst_env(char **envp)
{
	int		i;
	char	**line_splt;
	t_list	*res;
	t_env_var	*inter;

	res = 0;
	i = -1;
	while (envp[++i])
	{
		line_splt = ft_split(envp[i], '=');
		inter = malloc(sizeof(t_env_var));
		inter->name = ft_strdup(line_splt[0]);
		inter->value = ft_tabstrjoin(line_splt + 1);
		if (res)
			ft_lstadd_back(&res, ft_lstnew((void *)inter));
		else
			res = ft_lstnew((void *)inter);
	}
	return (res);
}

char	*get_val_var(t_list *lst, char *name)
{
	char	*res_null;
	t_list	*inter;

	inter = lst;
	while (inter->next)
	{
		if(!ft_strcmp(name, ((t_env_var *)inter->content)->name))
			return (((t_env_var *)inter->content)->value);
		inter = inter->next;
	}
	if(!ft_strcmp(name, ((t_env_var *)inter->content)->name))
		return (((t_env_var *)inter->content)->value);
	res_null = malloc (sizeof(char));
	*res_null = 0;
	return (res_null);
}

void	ft_lst_add_back_var(t_list *lst, char *name, char *val)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	new->name = ft_strdup(name);
	new->value = ft_strdup(val);
	ft_lstadd_back(&lst, ft_lstnew(new));
}

void	add_val(t_list *lst, char *name, char *val)
{
	char	*res;
	t_list	*inter;

	inter = lst;
	res = get_val_var(lst, name);
	if (!res[0])
		ft_lst_add_back_var(lst, ft_strdup(name), ft_strdup(val));
	else
	{
		while (inter->next)
		{
			if(!ft_strcmp(name, ((t_env_var *)inter->content)->name))
			{
				free(((t_env_var *)inter->content)->value);
				((t_env_var *)inter->content)->value = ft_strdup(val);
			}
			inter = inter->next;
		}
		if(!ft_strcmp(name, ((t_env_var *)inter->content)->name))
		{
			free(((t_env_var *)inter->content)->value);
			((t_env_var *)inter->content)->value = ft_strdup(val);
		}
	}
}

char	**get_env_in_char(t_list *env)
{
	int		i;
	t_list	*inter_l;
	char	**res;
	char	*inter;

	i = -1;
	res = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	inter_l = env;
	while (inter_l->next)
	{
		res[++i] = ft_strjoin(((t_env_var *)inter_l->content)->name, "=");
		inter = res[i];
		res[i] = ft_strjoin(res[i],((t_env_var *)inter_l->content)->value);
		free(inter);
		inter_l = (t_list *)inter_l->next;
	}
	res[++i] = ft_strjoin(((t_env_var *)inter_l->content)->name, "=");
	inter = res[i];
	res[i] = ft_strjoin(res[i],((t_env_var *)inter_l->content)->value);
	free(inter);
	res[++i] = NULL;
	return (res);
}
