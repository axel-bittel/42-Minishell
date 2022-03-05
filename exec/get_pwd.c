/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:24:19 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 21:32:40 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "exec_cmd.h"
#include "parsing.h"
#include <unistd.h>

char	*get_pwd(t_list *env)
{
	char	*res;

	res = get_val_var(env, "PWD");
	if (!*res)
	{
		free(res);
		res = malloc (sizeof(char) * 250);
		getcwd(res, 250);
		add_val(env, "PWD", res);
		free(res);
	}
	return (ft_strdup(get_val_var(env, "PWD")));
}

void	create_base_env(t_list **res, char *lunch)
{
	t_env_var	*inter;

	inter = malloc(sizeof(t_env_var *));
	inter->name = ft_strdup("PWD");
	inter->value = malloc(sizeof(char) * 255);
	getcwd(inter->value, 255);
	*res = ft_lstnew((void *)inter);
	inter = malloc(sizeof(t_env_var *));
	inter->name = ft_strdup("_");
	inter->value = ft_strdup(lunch);
	ft_lstadd_back(res, ft_lstnew((void *)inter));
}
