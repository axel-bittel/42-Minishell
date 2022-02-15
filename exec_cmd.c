/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/15 10:19:22 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "build_in.h"
#include "env_manager.h"
#include "parsing.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int	is_build_in(char *str)
{
	if(!ft_strcmp(str, "cd") || !ft_strcmp(str, "env") || \
!ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo"))
		return (1);
	return (0);
}

int	check_infile(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->in && cmd->in[++i])
	{
		//OPEN AND CHECK FILE
	}
	return (1);
}

int	exec_build_in(char **cmd, t_list *env)
{
	int	res;
	char	**env_chr;

	env_chr = get_env_in_char(env);
	if (!ft_strcmp("cd", cmd[0]))
		res = cd_bi(env, cmd);
	if (!ft_strcmp("pwd", cmd[0]))
		res = pwd_bi(env);
	if (!ft_strcmp("echo", cmd[0]))
		res = echo_bi(cmd);
	if (!ft_strcmp("env", cmd[0]))
		res = env_bi(env_chr);
	free_tabstr(env_chr);
	return (res);
}
int	exec_cmd(t_cmd *cmd, t_list *env)
{
	pid_t	pid;
	int	i;
	int	status;
	struct rusage	*rus;

	i = -1;
	rus = 0;
	check_infile(cmd);
	//FORKS
	while (cmd->cmd[++i])
	{
		if(is_build_in(cmd->cmd[i][0]))
			exec_build_in(cmd->cmd[i], env);
		else 
		{
			pid = fork();
			if(pid == 0)
			{
			}
			else
				wait4(pid, &status, 0, rus);
		}
	}
	//GET_RETURN RES OF FORKS
	return (0);
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
		return (exec_cmd ((t_cmd *)(cmd->content), env));
	}
}
