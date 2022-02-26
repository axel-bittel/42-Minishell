/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:38:46 by abittel           #+#    #+#             */
/*   Updated: 2022/02/27 00:27:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	free_tabint(cmd->pipes);
	while (cmd->cmd[++i])
	{
		free_tabstr(cmd->cmd[i]->cmd);
		free_tabstr(cmd->cmd[i]->in);
		free_tabstr(cmd->cmd[i]->hear_doc);
		free_tabstr(cmd->cmd[i]->out_add);
		free_tabstr(cmd->cmd[i]->out_replace);
		free_tabint(cmd->cmd[i]->fd_in);
		free_tabint(cmd->cmd[i]->fd_hear_doc);
		free_tabint(cmd->cmd[i]->fd_out_add);
		free_tabint(cmd->cmd[i]->fd_out_replace);
		free(cmd->cmd[i]);
	}
}

int	exit_bi(t_cmd *cmd, int i, int fd)
{
	int	stat;

	ft_putstr_fd("exit\n", fd);
	if(size_tabstr(cmd->cmd[i]->cmd) == 1)
	{
		free_cmd(cmd);
		exit(0);
	}
	else if(size_tabstr(cmd->cmd[i]->cmd) == 2)
	{
		stat = ft_atoi(cmd->cmd[i]->cmd[1]);
		free_cmd(cmd);
		exit (stat);
	}
	else
		ft_putstr_fd("BISCUIT: exit: ERROR ARGUMENT", 2);
	return (1);
}
