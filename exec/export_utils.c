/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:53:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/19 23:24:28 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "parsing.h"

int	get_end(char *cmd, int idx)
{
	int	idx_space;
	int	idx_eq;

	idx_space = get_idx_until_c(cmd, idx, ' ');
	idx_eq = get_idx_until_c(cmd, idx, '=');
	if (idx_space > 0 && idx_eq < 0)
		return (idx_space);
	else if (idx_space < 0 && idx_eq > 0)
		return (idx_eq);
	else if (idx_space < idx_eq)
		return (idx_space);
	else
		return (idx_eq);
}

char	*get_name(char **cmd, int *i, int *j) 
{
	char	*res;
	int		idx_end;

	res = malloc (sizeof(char) * 1);
	*res = 0;
	idx_end = get_end(cmd[*i], *j) - 1;
	while (cmd[*i] && idx_end < 0)
	{
		res = ft_strjoin(res, ft_strdup(cmd[*i] + *j));
		idx_end = get_end(cmd[*i], *j) - 1;
		(*j) = -1;
		(*i)++;
	}
	if (cmd[*i])
	{
		res = ft_strjoin(res, ft_substrdup(cmd[*i],  *j, idx_end));
		*j = idx_end;
	}
	return (res);
}

char	*get_val(char **cmd, int *i, int *j)
{
	char	*res;
	int		idx_end;

	(*j)++;
	res = malloc (sizeof(char) * 1);
	*res = 0;
	idx_end = get_idx_until_c(cmd[*i], *j, ' ');
	if (idx_end == -1)
	{
		res = ft_strjoin(res, ft_strdup(cmd[*i] + *j));
		(*j) = -1;
		(*i)++;
	}
	else
	{
		res = ft_strjoin(res, ft_substrdup(cmd[*i], *j, idx_end));
		*j = idx_end;
	}
	while (cmd[*i] && idx_end == -1)
	{
		idx_end = get_idx_until_c(cmd[*i], *j, ' ');
		if (*tok[*i] != TOKEN_REST || idx_end == -1)
		{
			res = ft_strjoin(res, ft_strdup(cmd[*i]));
			idx_end = -1;
			(*j) = -1;
			(*i)++;
		}
		else
		{
			res = ft_strjoin(res, ft_substrdup(cmd[*i], *j, idx_end));
			*j = idx_end;
		}
	}
	return (res);
}
