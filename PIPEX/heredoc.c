/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:00:16 by itaouil           #+#    #+#             */
/*   Updated: 2021/11/30 12:00:19 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd_heredoc(char **argv, char **envp, int cmd_no)
{
	char	*pathname;
	char	**execlist;

	pathname = get_pathname(envp, argv[cmd_no + 2]);
	if (!pathname)
	{
		ft_putstr_fd(argv[cmd_no + 1], 2);
		manage_errors(": Unknown command");
	}
	execlist = get_execve_list(envp, argv[cmd_no + 2]);
	execve(pathname, execlist, envp);
	manage_errors("Execve error");
}

static void	hd_pipe(char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		pipefd[2];
	pid_t	cpid;

	infile_fd = open("hdinfile", O_RDONLY);
	if (pipe(pipefd) == -1)
		manage_errors("pipe");
	cpid = fork();
	if (cpid == -1)
		manage_errors("fork");
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd_heredoc(argv, envp, 1);
	}
	close(pipefd[1]);
	outfile_fd = open(argv[5], O_RDWR | O_APPEND | O_CREAT, 0777);
	wait(NULL);
	unlink("hdinfile");
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	exec_cmd_heredoc(argv, envp, 2);
}

void	heredoc(char **argv, char **envp)
{
	char	*entry;
	int		infile_fd;

	infile_fd = open("hdinfile", O_RDWR | O_CREAT, 0777);
	entry = get_next_line(0);
	while (ft_strncmp(entry, argv[2], ft_strlen(argv[2])) != 0)
	{
		ft_putstr_fd(entry, infile_fd);
		entry = get_next_line(0);
	}
	hd_pipe(argv, envp);
}
