/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:55:39 by abittel           #+#    #+#             */
/*   Updated: 2022/02/15 18:49:47 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	size_tabstr(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i]);
	return (i);
}

int	size_tabtabstr(char ***str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i]);
	return (i);
}

int	size_tabint(int **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i]);
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

int	**ft_tabintjoin(int **tab, int* num)
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

void	free_tabstr(char **tab_str)
{
	int	i;

	i = -1;
	while (tab_str[++i])
		free(tab_str[i]);
	free(tab_str);
}

void	free_tabint(int **tab_int)
{
	int	i;

	i = -1;
	while (tab_int && tab_int[++i])
		free(tab_int[i]);
	if(tab_int)
		free(tab_int);
}
