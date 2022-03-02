/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:22:52 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/16 22:51:04 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	gnl_check_previous_rest(char **rest, char **line)
{
	if (rest)
	{
		*line = ft_new_strjoin(*line, *rest);
		free(*rest);
		*rest = NULL;
	}
}

void	gnl_fill_line(char **buffer, char **line, char **tmp)
{
	*tmp = ft_new_strjoin(*line, *buffer);
	free(*line);
	*line = ft_strdup(*tmp);
	free(*tmp);
}

char	*gnl_return_line(int count, char *line, char *tmp, char **rest)
{
	if (count <= 0 && line && line[0])
		return (line);
	else if (ft_new_strchr(line, '\n') >= 0)
	{
		tmp = ft_strndup(line, ft_new_strchr(line, '\n'));
		*rest = ft_strdup(line + (ft_new_strchr(line, '\n') + 1));
		free(line);
		return (tmp);
	}
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*buffer;
	char		*line;
	int			count;
	char		*tmp;

	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || read(fd, buffer, 0) < 0 || buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	gnl_check_previous_rest(&rest, &line);
	count = 1;
	while ((ft_new_strchr(line, '\n') < 0) && (count > 0))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		buffer[count] = 0;
		gnl_fill_line(&buffer, &line, &tmp);
	}
	free(buffer);
	return (gnl_return_line(count, line, tmp, &rest));
}
