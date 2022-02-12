/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeprof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:46:31 by abittel           #+#    #+#             */
/*   Updated: 2022/01/27 10:51:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_tree.h"

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_treeprof(t_tree *t)
{
	if (!t)
		return (0);
	return (max(ft_treeprof(t->f_a), ft_treeprof(t->f_b)) + 1);
}
