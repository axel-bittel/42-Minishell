/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:55:39 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 18:22:04 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "parsing.h"

int	size_tabint(int **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	**ft_tabintjoin(int **tab, int *num)
{
	int		i;
	int		**res;

	i = 0;
	res = malloc (sizeof(int *) * (size_tabint(tab) + 2));
	while (tab && tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i++] = num;
	res[i] = NULL;
	if (tab)
		free (tab);
	return (res);
}

int	size_tabcmd(t_sub_cmd **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

t_sub_cmd	**ft_cmdjoin(t_sub_cmd **cmd, t_sub_cmd *add)
{
	t_sub_cmd	**res;
	int			i;

	i = 0;
	res = malloc (sizeof(t_sub_cmd *) * (size_tabcmd(cmd) + 2));
	while (cmd && cmd[i])
	{
		res[i] = cmd[i];
		i++;
	}
	res[i++] = add;
	res[i] = NULL;
	if (cmd)
		free(cmd);
	return (res);
}

char	**ft_tabstrtrim(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc (sizeof(char *) * (size_tabstr(tab) + 1));
	while (tab && tab[i])
	{
		res[i] = ft_strtrim(tab[i], " ");
		i++;
	}
	res[i] = NULL;
	if (tab)
		free_tabstr(tab);
	return (res);
}
