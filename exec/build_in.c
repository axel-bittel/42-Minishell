/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:46:26 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 20:29:06 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "exec_cmd.h"

int	is_build_in(char *str)
{
	int		res;
	char	*str_trim;

	res = 0;
	str_trim = ft_strtrim(str, " ");
	if (!ft_strcmp(str_trim, "cd") || !ft_strcmp(str_trim, "env") || \
!ft_strcmp(str_trim, "pwd") || !ft_strcmp(str_trim, "echo") || \
!ft_strcmp(str_trim, "export") || !ft_strcmp(str_trim, "unset") || \
!ft_strcmp(str_trim, "exit"))
		res = 1;
	free(str_trim);
	return (res);
}

int	exec_build_in(t_cmd *cmd, t_list *env, int i, int fd)
{
	int		res;
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
