/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:21:06 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:21:47 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "utils.h"

void	free_tabstr(char **tab_str)
{
	int	i;

	i = -1;
	if (!tab_str)
		return ;
	while (tab_str[++i])
		free(tab_str[i]);
	free(tab_str);
}

void	free_tabint(int **tab_int)
{
	int	i;

	i = -1;
	if (!tab_int)
		return ;
	while (tab_int && tab_int[++i])
		free(tab_int[i]);
	if (tab_int)
		free(tab_int);
}

char	*ft_tabstrjoin(char **tab)
{
	int		i;
	char	*inter;
	char	*res;

	i = -1;
	inter = 0;
	res = 0;
	while (tab[++i])
	{
		inter = res;
		if (res)
			res = ft_strjoin(res, tab[i]);
		else
			res = ft_strdup(tab[i]);
		if (inter)
			free(inter);
	}
	return (res);
}

void	str_join_to_last(char **tab, char *str)
{
	char	*inter;

	inter = tab[size_tabstr(tab) - 1];
	tab[size_tabstr(tab) - 1] = ft_strjoin(tab[size_tabstr(tab) - 1], str);
	free(inter);
}
