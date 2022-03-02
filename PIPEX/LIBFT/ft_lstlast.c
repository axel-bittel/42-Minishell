/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:09:56 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/19 21:44:18 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pointer;

	if (!lst)
		return (NULL);
	if (!lst->next)
	{
		return (lst);
	}
	pointer = lst->next;
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
	}
	return (pointer);
}
