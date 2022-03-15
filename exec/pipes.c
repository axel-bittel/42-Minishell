/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:44:43 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 22:15:44 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "exec_cmd.h"
#include "libft.h"
#include <fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	get_pipes(t_cmd *cmd)
{
	int	i;
	int	size_tab;

	i = -1;
	size_tab = size_tabcmd(cmd->cmd);
	if (size_tab <= 0)
		return ;
	cmd->pipes = malloc(sizeof(int *) * (size_tab));
	cmd->pipes[size_tab - 1] = NULL;
	while (++i < size_tab - 1)
	{
		cmd->pipes[i] = malloc(sizeof(int) * 2);
		pipe(cmd->pipes[i]);
	}
}

void	wait_end_child(t_cmd *cmd, t_list *env, int *status)
{
	int		i;
	char	*inter_free;

	i = -1;
	while (cmd->cmd[++i])
	{
		waitpid(-1, status, 0);
		if (cmd->cmd[i]->cmd && !is_build_in(cmd->cmd[i]->cmd[0]))
		{
			if (WIFSIGNALED(*status))
				inter_free = ft_itoa(128 +  WTERMSIG(*status));
			else
				inter_free = ft_itoa(WEXITSTATUS(*status));
			add_val(env, "?", inter_free, 0);
			free(inter_free);
		}
	}
}

void	close_pipes(t_cmd *cmd, int idx)
{
	int	i;

	i = -1;
	if (!cmd->pipes)
		return ;
	while (cmd->pipes[++i] && i < idx)
	{
		close(cmd->pipes[i][0]);
		close(cmd->pipes[i][1]);
	}
}
