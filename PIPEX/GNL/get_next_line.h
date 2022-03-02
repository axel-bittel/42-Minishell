/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:48:58 by itaouil           #+#    #+#             */
/*   Updated: 2021/10/16 22:45:32 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../LIBFT/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFFER_SIZE 1024

int		ft_new_strchr(char *s, char c);
// char	*ft_strdup(char *s);
char	*ft_new_strjoin(char *s1, char *s2);
// int		ft_strlen(char *str);
char	*ft_strndup(char *str, int n);
char	*get_next_line(int fd);
void	gnl_check_previous_rest(char **rest, char **line);
void	gnl_fill_line(char **buffer, char **line, char **tmp);
char	*gnl_return_line(int count, char *line, char *tmp, char **rest);
#endif