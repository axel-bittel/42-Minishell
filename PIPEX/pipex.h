/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:00:58 by itaouil           #+#    #+#             */
/*   Updated: 2021/11/30 12:01:00 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "LIBFT/libft.h"
# include "GNL/get_next_line.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# define IN 1
# define OUT 0

void	check_arguments_nbr(int argc);
void	check_file(char **argv);
char	**get_execve_list(char **envp, char *argv);
char	*get_pathname(char **envp, char *argv);
void	heredoc(char **argv, char **envp);
void	manage_errors(char *error);
void	multi_pipex(char **argv, int argc, char **envp, int cmd_no);
void	pipe_and_fork(char **argv, char **envp);

#endif
