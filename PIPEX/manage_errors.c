/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:01:10 by itaouil           #+#    #+#             */
/*   Updated: 2021/11/30 12:01:12 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_arguments_nbr(int argc)
{
	if (argc < 5)
		manage_errors("Too few arguments");
}

void	check_file(char **argv)
{
	char	*file;

	file = argv[1];
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		manage_errors(": Non-existing file");
	}
}

void	manage_errors(char *error)
{
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}
