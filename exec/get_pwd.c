/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:24:19 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 13:32:21 by abittel          ###   ########.fr       */
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
