/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/03/22 23:55:15 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "build_in.h"
#include "utils.h"
#include "exec_cmd.h"
#include "parsing.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>

void	exec_sys_error(char *inter_path, char **args)
{
	char	*f_cmd;

	free(inter_path);
	if (!is_path(args[0]))
	{
		ft_putstr_fd("minishell: COMMAND NOT FOUND\n", 2);
		exit (127);
	}
	f_cmd = ft_strjoin("minishell:", args[0]);
	if (is_path(args[0]))
		perror(f_cmd);
	free(f_cmd);
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
	inter_path = get_absolute_path(envp, args[0]);
	if (!is_absolute_path(args[0]))
		execve(inter_path, args, get_env_in_char(envp));
	else
		execve(args[0], args, get_env_in_char(envp));
	exec_sys_error(inter_path, args);
	if (errno != 13)
		exit (1);
	exit (126);
}

int	exec_sub_cmd(t_cmd *cmd, int *i, t_list *env)
{
	int		i_bis;
	char	*res;

	i_bis = *i;
	if (!cmd->cmd || !cmd->cmd[*i] || !cmd->cmd[*i]->cmd)
		return (i_bis);
	if (is_build_in(cmd->cmd[*i]->cmd[0]))
	{
		if (cmd->cmd[*i + 1])
			i_bis = exec_sub_cmd(cmd, ((++i_bis), &i_bis), env);
		dup_manager(cmd, *i, 1);
		res = ft_itoa(exec_build_in(cmd, env, *i, g_sig.new_stdout));
		add_val(env, "?", res, 0);
		free(res);
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
		cmd->cmd[i]->hear_doc = ft_tabstrtrim(cmd->cmd[i]->hear_doc);
		if (check_file(cmd->cmd[i]->in, &(cmd->cmd[i]->fd_in), O_APPEND) || \
check_file(cmd->cmd[i]->out_replace, &(cmd->cmd[i]->fd_out_replace), \
O_WRONLY | O_TRUNC | O_CREAT) || check_file(cmd->cmd[i]->out_add, \
&(cmd->cmd[i]->fd_out_add), O_WRONLY | O_APPEND | O_CREAT) || \
read_heardocs(cmd->cmd[i], env))
			return (add_val(env, "?", "1", 0), 1);
		i = exec_sub_cmd(cmd, &i, env);
	}
	close_pipes(cmd, size_tabcmd(cmd->cmd));
	wait_end_child(cmd, env, &status);
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
