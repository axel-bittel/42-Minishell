/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:36:05 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 16:52:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "exec_cmd.h"

void	free_env_var(t_env_var *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}

void	ft_lst_add_back_var(t_list *lst, char *name, char *val, int is_export)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	new->name = ft_strdup(name);
	new->value = ft_strdup(val);
	new->is_export = is_export;
	ft_lstadd_back(&lst, ft_lstnew(new));
}

void	delete_elem(t_list **lst, t_list *inter, t_list *prec)
{
	if (prec)
		prec->next = inter->next;
	else
		*lst = inter->next;
	if ((t_env_var *)inter->content)
		free_env_var((t_env_var *)inter->content);
	if (inter)
		free(inter);
}

void	add_val_not_exist(t_list *lst, char *name, char *val, int is_export)
{
	char	*name_dup;
	char	*val_dup;

	val_dup = ft_strdup(val);
	name_dup = ft_strdup(name);
	if (!val_dup)
	{
		val_dup = malloc(sizeof(char) * 1);
		val_dup[0] = 0;
	}
	if (!name_dup)
	{
		name_dup = malloc(sizeof(char) * 1);
		name_dup[0] = 0;
	}
	ft_lst_add_back_var(lst, name_dup, val_dup, is_export);
	free(val_dup);
	free(name_dup);
}

void	free_env(t_list *env)
{
	t_list	*inter;
	t_list	*nxt;

	inter = env;
	while (inter->next)
	{
		nxt = inter->next;
		free_env_var((t_env_var *)inter->content);
		free(inter);
		inter = nxt;
	}
	free_env_var((t_env_var *)inter->content);
	free(inter);
}
