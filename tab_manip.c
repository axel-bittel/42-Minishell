/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:55:39 by abittel           #+#    #+#             */
/*   Updated: 2022/02/21 21:34:27 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "parsing.h"

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

int	size_tabcmd(t_sub_cmd **tab)
{
	int	i;

	i = 0;
	if(!tab)
		return (0);
	while(tab[i])
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

char	**ft_tabstrtrim(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc (sizeof(char *) * (size_tabstr(tab) + 1));
	while(tab && tab[i])
	{
		res[i] = ft_strtrim(tab[i], " ");
		i++;
	}
	res[i] = NULL;
	if (tab)
		free_tabstr(tab);
	return (res);
}
