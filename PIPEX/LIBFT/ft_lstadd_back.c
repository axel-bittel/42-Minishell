/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:09:12 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:09:14 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*pointer;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	pointer = *alst;
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
	}
	pointer->next = new;
}
