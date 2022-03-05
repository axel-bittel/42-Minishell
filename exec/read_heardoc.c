/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heardoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:41:28 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 19:26:42 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>
#include "exec_cmd.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <errno.h>

void	read_heardoc_addline(char *line, char **res, char **inter)
{
	if (*res)
		*inter = *res;
	*res = ft_strjoin(*res, line);
	if (*res)
		free(*inter);
	*inter = *res;
	*res = ft_strjoin(*res, "\n");
	free(*inter);
	if (line)
		free(line);
}

char	*read_heardoc(char *end)
{
	char	*res;
	char	*inter;
	char	*line;
	int		find_end;

	res = malloc(sizeof(char));
	*res = 0;
	inter = 0;
	find_end = 0;
	while (!find_end)
	{
		rl_on_new_line();
		line = readline(">");
		if (!ft_strcmp(line, end))
			find_end = 1;
		else
			read_heardoc_addline(line, &res, &inter);
	}
	return (res);
}

char	*get_name_hd(int i)
{
	char	*res;
	char	*inter;

	res = ft_itoa(i);
	inter = res;
	res = ft_strjoin("/tmp/.biscuit_hd", res);
	free(inter);
	return (res);
}

int	read_heardocs(t_sub_cmd *cmd, t_list *env)
{
	int		i;
	int		*fd;
	char	*line_heardoc;
	char	*name;

	i = -1;
	while (cmd->hear_doc && cmd->hear_doc[++i])
	{
		name = get_name_hd(i);
		fd = malloc(sizeof(int));
		*fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (!*fd)
			return (errno);
		line_heardoc = read_heardoc(cmd->hear_doc[i]);
		expand_var(&line_heardoc, env);
		ft_putstr_fd (line_heardoc, *fd);
		close(*fd);
		*fd = open(name, O_RDWR);
		cmd->fd_hear_doc = ft_tabintjoin(cmd->fd_hear_doc, fd);
		free(name);
	}
	return (0);
}

int	check_file(char **names, int ***fd_tab, int ARG)
{
	int		i;
	int		*inter_fd;
	char	*error_msg;

	i = -1;
	while (names && names[++i])
	{
		inter_fd = malloc(sizeof(int));
		*inter_fd = open(names[i], ARG, 0666);
		if (*inter_fd == -1)
		{
			error_msg = ft_strjoin("BISCUIT: ", names[i]);
			perror(error_msg);
			free(inter_fd);
			return (1);
		}
		else
			*fd_tab = ft_tabintjoin(*fd_tab, inter_fd);
	}
	return (0);
}
