/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/28 12:06:17 by abittel          ###   ########.fr       */
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
!ft_strcmp(str_trim, "pwd") || !ft_strcmp(str_trim, "echo") || !ft_strcmp(str_trim, "export") \
|| !ft_strcmp(str_trim, "unset") || !ft_strcmp(str_trim, "exit"))
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
		{
			if (*res)
				inter = res;
			res = ft_strjoin(res, "\n");
			if (inter)
				free(inter);
			inter = res;
			res = ft_strjoin(res, line);
			free(inter);
			if (line)
				free(line);
		}
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
		expand_VAR(&line_heardoc, env);
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
			if (errno == EACCES)
				return (errno = 126, 126);
			else
				return (1);
		}
		else
			*fd_tab = ft_tabintjoin(*fd_tab, inter_fd);
	}
	return (0);
}

void	dup_manager(t_cmd *cmd, int i, int is_bi)
{
	if (cmd->cmd[i]->fd_in || cmd->cmd[i]->fd_hear_doc)
	{
		g_sig.old_stdin = dup(0);
		if(cmd->cmd[i]->last_is_in == 1)
		{
			g_sig.new_stdin = dup2(*cmd->cmd[i]->fd_in[size_tabint(cmd->cmd[i]->fd_in) - 1], 0);
			g_sig.new_stdin = *cmd->cmd[i]->fd_in[size_tabint(cmd->cmd[i]->fd_in) - 1];
		}
		else
		{
			g_sig.new_stdin = dup2(*cmd->cmd[i]->fd_hear_doc[size_tabint(cmd->cmd[i]->fd_hear_doc) - 1], 0);
			g_sig.new_stdin = *cmd->cmd[i]->fd_hear_doc[size_tabint(cmd->cmd[i]->fd_hear_doc) - 1];
		}
	}
	else if(i)
	{
		g_sig.old_stdin = dup(0);
		g_sig.new_stdin = dup2(cmd->pipes[i - 1][0], 0);
		g_sig.new_stdin = cmd->pipes[i - 1][0];
	}
	else if(size_tabcmd(cmd->cmd) > 1)
		close(cmd->pipes[i][0]);
	if (cmd->cmd[i]->fd_out_add || cmd->cmd[i]->fd_out_replace)
	{
		g_sig.old_stdout = dup(1);
		if(cmd->cmd[i]->last_is_add == 1)
		{
			g_sig.new_stdout = dup2(*cmd->cmd[i]->fd_out_add[size_tabint(cmd->cmd[i]->fd_out_add) - 1], 1);
			g_sig.new_stdout = *cmd->cmd[i]->fd_out_add[size_tabint(cmd->cmd[i]->fd_out_add) - 1];
		}
		if(cmd->cmd[i]->last_is_add == 0)
		{
			g_sig.new_stdout = dup2(*cmd->cmd[i]->fd_out_replace[size_tabint(cmd->cmd[i]->fd_out_replace) - 1], 1);
			g_sig.new_stdout = *cmd->cmd[i]->fd_out_replace[size_tabint(cmd->cmd[i]->fd_out_replace) - 1];
		}
		if(size_tabcmd(cmd->cmd) > 1 && i != size_tabint(cmd->pipes))
			close(cmd->pipes[i][1]);
	}
	else if (i != size_tabint(cmd->pipes))
	{
		if(is_bi)
			g_sig.old_stdout = dup(1);
		g_sig.new_stdout = dup2(cmd->pipes[i][1], 1);
		g_sig.new_stdout = cmd->pipes[i][1];
	}
	else if(size_tabcmd(cmd->cmd) > 1 && i != size_tabint(cmd->pipes))
		close(cmd->pipes[i][1]);
	else if(is_bi)
		g_sig.new_stdout = 1;
}

void	close_pipes(t_cmd *cmd, int idx)
{
	int	i;

	i = -1;
	while (cmd->pipes[++i] && i < idx)
	{
		close(cmd->pipes[i][0]);
		close(cmd->pipes[i][1]);
	}
}

void	re_dup(t_cmd *cmd, int i)
{
	close_pipes(cmd, i);
	dup2(g_sig.old_stdin, 0);
	dup2(g_sig.old_stdout, 1);
}

int	exec_build_in(t_cmd *cmd, t_list *env, int i, int fd)
{
	int	res;
	char	**env_chr;
	char	*cmd_trim;

	env_chr = get_env_in_char(env);
	cmd_trim = ft_strtrim(cmd->cmd[i]->cmd[0], " ");
	if (!ft_strcmp("cd", cmd_trim))
		res = cd_bi(env, cmd->cmd[i]->cmd);
	if (!ft_strcmp("pwd", cmd_trim))
		res = pwd_bi(env, fd);
	if (!ft_strcmp("echo", cmd_trim))
		res = echo_bi(cmd->cmd[i]->cmd, fd);
	if (!ft_strcmp("env", cmd_trim))
		res = env_bi(env_chr, fd);
	if (!ft_strcmp("export", cmd_trim))
		res = export_bi(cmd->cmd[i]->cmd, env, i);
	if (!ft_strcmp("unset", cmd_trim))
		res = unset_bi(cmd->cmd[i]->cmd, env);
	if (!ft_strcmp("exit", cmd_trim))
		res = exit_bi(cmd, i, fd, env);
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
	if (!is_absolute_path(args[0]))
		execve(get_absolute_path(envp, args[0]), args, get_env_in_char(envp));
	else
		execve(args[0], args, get_env_in_char(envp));
	f_cmd = ft_strjoin("BISCUIT:", args[0]);
	perror(f_cmd);
	free(f_cmd);
	exit (errno);
}

int	exec_sub_cmd(t_cmd *cmd, int *i, t_list *env)
{
	int	i_bis;

	i_bis = *i;
	if(is_build_in(cmd->cmd[*i]->cmd[0]))
	{
		if (cmd->cmd[*i + 1])
			i_bis = exec_sub_cmd(cmd, ((++i_bis), &i_bis), env);
		dup_manager(cmd, *i, 1);
		add_val(env, "?", ft_itoa(exec_build_in(cmd, env, *i, g_sig.new_stdout)));
		close_pipes(cmd, *i);
		re_dup(cmd, *i);
	}
	else if (fork() == 0)
	{
		dup_manager(cmd, *i, 0);
		cmd->cmd[*i]->cmd = ft_tabstrtrim(cmd->cmd[*i]->cmd);
		close_pipes(cmd, *i);
		exec_sys_cmd(cmd->cmd[*i]->cmd, env);
	}
	return (i_bis);
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
	status = 0;
	get_pipes(cmd);
	while (cmd->cmd && cmd->cmd[++i])
	{
		cmd->cmd[i]->in = ft_tabstrtrim(cmd->cmd[i]->in);
		cmd->cmd[i]->out_replace = ft_tabstrtrim(cmd->cmd[i]->out_replace);
		cmd->cmd[i]->out_add = ft_tabstrtrim(cmd->cmd[i]->out_add);
		cmd->cmd[i]->hear_doc= ft_tabstrtrim(cmd->cmd[i]->hear_doc);
		if(check_file(cmd->cmd[i]->in, &(cmd->cmd[i]->fd_in), O_APPEND) || \
check_file(cmd->cmd[i]->out_replace, &(cmd->cmd[i]->fd_out_replace), O_WRONLY | O_TRUNC | O_CREAT) || \
check_file(cmd->cmd[i]->out_add, &(cmd->cmd[i]->fd_out_add), O_WRONLY | O_APPEND | O_CREAT) ||
read_heardocs(cmd->cmd[i], env))
			return (add_val(env, "?", ft_itoa(errno)), 1);
		i = exec_sub_cmd(cmd, &i, env);
	}
	close_pipes(cmd, size_tabcmd(cmd->cmd));
	i = -1;
	while(cmd->cmd[++i])
	{
		waitpid(-1, &status, 0);
		add_val(env, "?", ft_itoa(WEXITSTATUS(status)));
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
		return (exec_cmd((t_cmd *)(cmd->content), env));
}
