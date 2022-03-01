/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:10:17 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/18 11:25:00 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*counter;

	if (!lst)
		return (0);
	count = 1;
	counter = lst->next;
	while (counter != NULL)
	{
		count++;
		counter = counter->next;
	}
	return (count);
}
