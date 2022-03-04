/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:18:42 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 18:20:21 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	size_tabstr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	size_tabtabstr(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_tabjoin(char **tab, char *str)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc (sizeof(char *) * (size_tabstr(tab) + 2));
	while (tab && tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i++] = str;
	res[i] = NULL;
	if (tab)
		free(tab);
	return (res);
}

char	***ft_tabtabjoin(char ***tab, char **tab_add)
{
	int		i;
	char	***res;

	i = 0;
	res = malloc (sizeof(char **) * (size_tabtabstr(tab) + 2));
	while (tab && tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i++] = tab_add;
	res[i] = NULL;
	if (tab)
		free(tab);
	return (res);
}

char	*ft_substrdup(char	*str, int start, int end)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc (sizeof(char) * end - start + 2);
	while (++i < (end - start + 1))
		res[i] = str[start + i];
	res[end - start + 1] = 0;
	return (res);
}
