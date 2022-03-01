/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:00:27 by itaouil           #+#    #+#             */
/*   Updated: 2021/11/30 12:00:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char **argv, char **envp, int cmd_no)
{
	char	*pathname;
	char	**execlist;

	pathname = get_pathname(envp, argv[cmd_no + 1]);
	if (!pathname)
	{
		ft_putstr_fd(argv[cmd_no + 1], 2);
		manage_errors(": Unknown command");
	}
	execlist = get_execve_list(envp, argv[cmd_no + 1]);
	execve(pathname, execlist, envp);
	manage_errors("Execve error");
}

static void	if_first_command(char **argv, int cmd_no, int *infile_fd)
{
	if (cmd_no == 1)
	{
		*infile_fd = open(argv[1], O_RDONLY, 0777);
		dup2(*infile_fd, STDIN_FILENO);
	}
}

static void	exit_if_last_cmd(char **argv, int argc, char **envp, int *cmd_no)
{
	while (*cmd_no < (argc - 3))
		multi_pipex(argv, argc, envp, (*(cmd_no) + 1));
	exit(EXIT_SUCCESS);
}

void	multi_pipex(char **argv, int argc, char **envp, int cmd_no)
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	cpid;

	if (pipe(pipefd) == -1)
		manage_errors("Pipe error");
	cpid = fork();
	if (cpid == -1)
		manage_errors("Fork error");
	if (cpid == 0)
	{
		close(pipefd[OUT]);
		if_first_command(argv, cmd_no, &infile);
		if (cmd_no == (argc - 3))
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			outfile = pipefd[IN];
		dup2(outfile, STDOUT_FILENO);
		exec_cmd(argv, envp, cmd_no);
	}
	close(pipefd[IN]);
	wait(NULL);
	dup2(pipefd[OUT], STDIN_FILENO);
	exit_if_last_cmd(argv, argc, envp, &cmd_no);
}

int	main(int argc, char *argv[], char *envp[])
{
	check_arguments_nbr(argc);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc != 6)
			manage_errors("Wrong number of arguments");
		if (!get_pathname(envp, argv[3]) || !get_pathname(envp, argv[4]))
		{
			if (!get_pathname(envp, argv[3]))
				ft_putstr_fd(argv[3], 2);
			else
				ft_putstr_fd(argv[4], 2);
			manage_errors(": Unknown command");
		}
		heredoc(argv, envp);
		exit(EXIT_SUCCESS);
	}
	check_file(argv);
	multi_pipex(argv, argc, envp, 1);
}
