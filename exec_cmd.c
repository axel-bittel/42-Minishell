/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/21 21:47:31 by abittel          ###   ########.fr       */
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

int	exec_sys_cmd(char **args, t_list *envp)
{
	int		i;
	char	*f_cmd;
	char	**paths;
	char	*inter_path;

	i = -1;
	if (!is_absolute_path(args[0]))
	{
		paths = ft_split(get_val_var(envp, "PATH"), ':');
		while (paths[++i])
		{
			inter_path = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(inter_path, args[0]);
			if (access(f_cmd, F_OK | X_OK) == 0)
				execve(f_cmd, args, get_env_in_char(envp));
			free(inter_path);
			free(f_cmd);
		}
	}
	else
		execve(args[0], args, get_env_in_char(envp));
	f_cmd = ft_strjoin("BISCUIT:", args[0]);
	perror(f_cmd);
	free(f_cmd);
	return (0);
}

void	close_pipes(t_cmd *cmd, int idx)
{
	int	i;

	i = -1;
	while (cmd->pipes[i] && ++i < idx)
		close(cmd->pipes[i][0]);
}

int	exec_sub_cmd(t_cmd *cmd, int i, t_list *env)
{
	//close_pipes(cmd, i);
	if (cmd->cmd[i]->fd_in)
		dup2(*cmd->cmd[i]->fd_in[size_tabint(cmd->cmd[i]->fd_in) - 1], 0);
	else if(i)
		dup2(cmd->pipes[i - 1][1], 0);
	else
		close(0);
	if (cmd->cmd[i]->fd_out_add || cmd->cmd[i]->fd_out_replace)
	{
		if(cmd->cmd[i]->last_is_add == 1)
			dup2(*cmd->cmd[i]->fd_out_add[size_tabint(cmd->cmd[i]->fd_out_add) - 1], 1);
		if(cmd->cmd[i]->last_is_add == 0)
			dup2(*cmd->cmd[i]->fd_out_replace[size_tabint(cmd->cmd[i]->fd_out_replace) - 1], 1);
	}
	cmd->cmd[i]->cmd = ft_tabstrtrim(cmd->cmd[i]->cmd);
	exec_sys_cmd(cmd->cmd[i]->cmd, env);
	return (0);
}

void	get_pipes(t_cmd *cmd)
{
	int	i;
	int	size_tab;

	i = -1;
	size_tab = size_tabcmd(cmd->cmd);
	cmd->pipes = malloc(sizeof(int *) * (size_tab));
	cmd->pipes[size_tab - 1] = NULL;
	while(++i < size_tab - 1)
	{
		cmd->pipes[i] = malloc(sizeof(int) * 2);
		pipe(cmd->pipes[i]);
	}
}

int	exec_cmd(t_cmd *cmd, t_list *env)
{
	int	i;
	int	status;

	i = -1;
	get_pipes(cmd);
	while (cmd->cmd[++i])
	{
		cmd->cmd[i]->in = ft_tabstrtrim(cmd->cmd[i]->in);
		cmd->cmd[i]->out_replace = ft_tabstrtrim(cmd->cmd[i]->out_replace);
		cmd->cmd[i]->out_add = ft_tabstrtrim(cmd->cmd[i]->out_add);
		if(check_file(cmd->cmd[i]->in, &(cmd->cmd[i]->fd_in), O_APPEND) || \
check_file(cmd->cmd[i]->out_replace, &(cmd->cmd[i]->fd_out_replace), O_APPEND | O_TRUNC | O_CREAT) || \
check_file(cmd->cmd[i]->out_add, &(cmd->cmd[i]->fd_out_add), O_APPEND | O_CREAT))
			return (127);
		if(is_build_in(cmd->cmd[i]->cmd[0]))
			status = exec_build_in(cmd->cmd[i]->cmd, env);
		else 
		{
			if (fork() == 0)
				exec_sub_cmd(cmd, i, env);
		}
	}
	waitpid(-1, 0, 0);
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
