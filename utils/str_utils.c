/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:40:20 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 18:05:54 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	get_deb_word(char *str, int i)
{
	while (i >= 0 && str[i] != ' ')
		i--;
	return (i + 1);
}

char	get_end_word(char *str, int i)
{
	while (str[i] && str[i] != ' ')
		i++;
	return (i - 1);
}

int	is_path(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

char	*insert_str(char *str, char *str_ins, int *deb, int end)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = -1;
	j = -1;
	k = end;
	res = malloc (sizeof(char) * (ft_strlen(str_ins) + ft_strlen(str) - \
	(*deb - end + 1) + 1));
	while (++i < *deb)
		res[i] = str[i];
	while (++j < (int)ft_strlen(str_ins))
		res[i + j] = str_ins[j];
	while (str[++k])
		res[i + j++] = str[k];
	res[i + j] = 0;
	*deb += ft_strlen(str_ins) - 1;
	free(str);
	free(str_ins);
	return (res);
}

int	nb_chr_in_str(char *str, char chr)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] == chr)
			res++;
	return (res);
}
