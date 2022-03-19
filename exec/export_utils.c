/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:53:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/20 00:32:27 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
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

int	get_name_utils(t_sub_cmd *cmd, int *i, int *j, char **res)
{
	int	idx_end;

	*res = malloc (sizeof(char) * 1);
	**res = 0;
	idx_end = get_end(cmd->cmd[*i], *j) - 1;
	while (cmd->cmd[*i] && idx_end < 0)
	{
		*res = ft_strjoin3(*res, ft_strdup(cmd->cmd[*i] + *j));
		idx_end = get_end(cmd->cmd[*i], *j) - 1;
		(*j) = -1;
		(*i)++;
	}
	return (idx_end);
}

char	*get_name(t_sub_cmd *cmd, int *i, int *j)
{
	char	*res;
	int		idx_end;
	char	*inter;

	idx_end = get_name_utils(cmd, i, j, &res);
	if (cmd->cmd[*i])
	{
		if (*cmd->token[*i] == TOKEN_REST)
		{
			inter = ft_substrdup(cmd->cmd[*i], *j, idx_end);
			res = ft_strjoin3(res, inter);
			*j = idx_end;
		}
		else
		{
			res = ft_strjoin3(res, ft_strdup(cmd->cmd[*i] + *j));
			*j = -1;
		}
	}
	return (res);
}

int	get_val_utils(t_sub_cmd *cmd, int *i, int *j, char **res)
{
	int		idx_end;

	*res = malloc (sizeof(char) * 1);
	**res = 0;
	idx_end = get_idx_until_c(cmd->cmd[*i], *j, ' ');
	if (idx_end == -1)
	{
		*res = ft_strjoin3(*res, ft_strdup(cmd->cmd[*i] + *j + 1));
		(*j) = -1;
		(*i)++;
	}
	else
	{
		*res = ft_strjoin3(*res, ft_substrdup(cmd->cmd[*i], *j + 1, idx_end));
		*j = idx_end;
	}
	return (idx_end);
}

char	*get_val(t_sub_cmd *cmd, int *i, int *j)
{
	char	*res;
	int		idx_end;

	idx_end = get_val_utils(cmd, i, j, &res);
	while (cmd->cmd[*i] && idx_end == -1)
	{
		idx_end = get_idx_until_c(cmd->cmd[*i], *j, ' ');
		if (*cmd->token[*i] != TOKEN_REST || idx_end == -1)
		{
			res = ft_strjoin3(res, ft_strdup(cmd->cmd[*i]));
			idx_end = -1;
			(*j) = -1;
			(*i)++;
		}
		else
		{
			res = ft_strjoin3(res, ft_substrdup(cmd->cmd[*i], *j, idx_end));
			*j = idx_end;
		}
	}
	return (res);
}
