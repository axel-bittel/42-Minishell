/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/18 17:57:51 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "build_in.h"
#include "env_manager.h"
#include "parsing.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>

int	is_build_in(char *str)
{
	int		res;
	char	*str_trim;

	res = 0;
	str_trim = ft_strtrim(str, " ");
	if(!ft_strcmp(str_trim, "cd") || !ft_strcmp(str_trim, "env") || \
!ft_strcmp(str_trim, "pwd") || !ft_strcmp(str_trim, "echo") || !ft_strcmp(str_trim, "export"))
		res = 1;
	free(str_trim);
	return (res);
}

char	*read_heardoc(char *end)
{
	char	*res;
	char	*inter;
	char	*line;
	int		find_end;

	find_end = 0;
	while (!find_end)
	{
		rl_on_new_line();
		line = readline(" >");
		if (!ft_strcmp(res, end))
			find_end = 1;
		else
		{
			inter = res;
			res = ft_strjoin(res, line);
			free(inter);
			free(line);
		}
	}
	return (res);
}

int	check_file(char **names, int ***fd_tab, int ARG)
{
	int	i;
	int	*inter_fd;
	char	*error_msg;

	i = -1;
	while (names && names[++i])
	{
		inter_fd = malloc(sizeof(int));
		*inter_fd = open(names[i], ARG, 0666);
		if (*inter_fd== -1)
		{
			error_msg = ft_strjoin("BISCUIT: ", names[i]);
			perror(error_msg);
			free(inter_fd);
			free(names[i]);
			return (errno);
		}
		else
			*fd_tab = ft_tabintjoin(*fd_tab, inter_fd);
	}
	return (0);
}

int	exec_build_in(char **cmd, t_list *env)
{
	int	res;
	char	**env_chr;
	char	*cmd_trim;

	cmd_trim = ft_strtrim(cmd[0], " ");
	env_chr = get_env_in_char(env);
	if (!ft_strcmp("cd", cmd_trim))
		res = cd_bi(env, cmd);
	if (!ft_strcmp("pwd", cmd_trim))
		res = pwd_bi(env);
	if (!ft_strcmp("echo", cmd_trim))
		res = echo_bi(cmd);
	if (!ft_strcmp("env", cmd_trim))
		res = env_bi(env_chr);
	if (!ft_strcmp("export", cmd_trim))
		res = export_bi(cmd, env);
	free_tabstr(env_chr);
	free (cmd_trim);
	return (res);
}

int	exec_sub_cmd(char **cmd, t_list *env, int *pipe)
{
	(void)cmd;
	(void)env;
	(void)pipe;
	return (0);
}

int	exec_cmd(t_cmd *cmd, t_list *env)
{
	int	i;
	int	old_pipe;
	int	pipe_proc[2];
	int	status;

	i = -1;
	old_pipe = 0;
	check_file(cmd->in, &(cmd->fd_in), O_APPEND);
	check_file(cmd->out_replace, &(cmd->fd_out_replace), O_APPEND | O_TRUNC | O_CREAT);
	check_file(cmd->out_add, &(cmd->fd_out_add), O_APPEND | O_CREAT);
	while (cmd->cmd[++i])
	{
		if(is_build_in(cmd->cmd[i][0]))
			status = exec_build_in(cmd->cmd[i], env);
		else 
		{
			if (cmd->cmd[i + 1])
			{
				if (old_pipe)
				old_pipe = pipe_proc[1];
				pipe(pipe_proc);
			}
			if (fork() == 0)
				exec_sub_cmd(cmd->cmd[i], env, pipe_proc);
		}
	}
	return (status);
}

int	exec_tree_cmd(t_tree *cmd, t_list *env)
{
	int	res_a;
	int	res_b;

	if (cmd->f_a && cmd->f_b)
	{
		res_a = exec_tree_cmd((t_tree *)cmd->f_a, env);
		if ((*(int *)(cmd->content) == OP_AND && !res_a) || \
(*(int *)(cmd->content) == OP_OR && res_a))
		{
			res_b = exec_tree_cmd((t_tree *)(cmd->f_b), env);
			return (res_b);
		}
		return (res_a);
	}
	else
	{
		return (exec_cmd((t_cmd *)(cmd->content), env));
	}
}
