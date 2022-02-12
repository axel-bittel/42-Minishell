/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeadd_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:41:08 by abittel           #+#    #+#             */
/*   Updated: 2022/01/27 10:45:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_tree.h"

void	ft_treeadd_f(t_tree *t, t_tree *f, int is_a)
{
	if (!t)
		return ;
	if (is_a)
		t->f_a = (struct s_tree *)f;
	else
		t->f_b = f;
}
