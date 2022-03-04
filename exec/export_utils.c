/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:53:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:29:53 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
