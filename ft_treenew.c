/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:54:10 by abittel           #+#    #+#             */
/*   Updated: 2022/02/01 17:13:40 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_tree.h"
#include <stdlib.h>
#include <stddef.h>

t_tree	*ft_treenew(void *content)
{
	t_tree	*res;

	if (!content)
		return (NULL);
	res = (t_tree *)malloc(sizeof(t_tree));
	if (!res)
		return (NULL);
	res->f_a = NULL;
	res->f_b = NULL;
	res->content = content;
	return (res);
}
t_tree	*ft_treenew_fill (void *content, t_tree *fils_a, t_tree *fils_b)
{
	t_tree	*res;

	res = (t_tree *)malloc(sizeof(t_tree));
	if (!res)
		return (NULL);
	res->f_a = fils_a;
	res->f_b = fils_b;
	res->content = content;
	return (res);
}
