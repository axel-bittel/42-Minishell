/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:43:09 by abittel           #+#    #+#             */
/*   Updated: 2022/03/14 23:01:57 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include "parsing.h"
#include "exec_cmd.h"

void	dup_manager_read(t_cmd *cmd, int i, t_sub_cmd *c, int is_bi)
{
	if (cmd->cmd[i]->fd_in || cmd->cmd[i]->fd_hear_doc)
	{
		g_sig.old_stdin = dup(0);
		if (cmd->cmd[i]->last_is_in == 1)
		{
			g_sig.new_stdin = dup2(*c->fd_in[size_tabint(c->fd_in) - 1], 0);
			g_sig.new_stdin = *c->fd_in[size_tabint(c->fd_in) - 1];
		}
		else
		{
			g_sig.new_stdin = dup2(*c->fd_hear_doc[\
size_tabint(c->fd_hear_doc) - 1], 0);
			g_sig.new_stdin = *c->fd_hear_doc[size_tabint(c->fd_hear_doc) - 1];
		}
	}
	else if (i)
	{
		g_sig.old_stdin = dup(0);
		g_sig.new_stdin = dup2(cmd->pipes[i - 1][0], 0);
		g_sig.new_stdin = cmd->pipes[i - 1][0];
	}
	else if (size_tabcmd(cmd->cmd) > 1 && !is_bi)
		close(cmd->pipes[i][0]);
}

int	dup_manager_write(t_cmd *cmd, int i, t_sub_cmd *c)
{
	if (cmd->cmd[i]->fd_out_add || cmd->cmd[i]->fd_out_replace)
	{
		g_sig.old_stdout = dup(1);
		if (cmd->cmd[i]->last_is_add == 1)
		{
			g_sig.new_stdout = dup2(*c->fd_out_add[\
size_tabint(c->fd_out_add) - 1], 1);
			g_sig.new_stdout = *c->fd_out_add[size_tabint(c->fd_out_add) - 1];
		}
		if (cmd->cmd[i]->last_is_add == 0)
		{
			g_sig.new_stdout = dup2(*c->fd_out_replace[\
size_tabint(c->fd_out_replace) - 1], 1);
			g_sig.new_stdout = *c->fd_out_replace[\
size_tabint(c->fd_out_replace) - 1];
		}
		if (size_tabcmd(cmd->cmd) > 1 && i != size_tabint(cmd->pipes))
			close(cmd->pipes[i][1]);
	}
	else
		return (0);
	return (1);
}

void	dup_manager(t_cmd *cmd, int i, int is_bi)
{
	t_sub_cmd	*c;

	c = cmd->cmd[i];
	dup_manager_read(cmd, i, c, is_bi);
	if (dup_manager_write(cmd, i, c))
		return ;
	else if (i != size_tabint(cmd->pipes))
	{
		if (is_bi)
			g_sig.old_stdout = dup(1);
		g_sig.new_stdout = dup2(cmd->pipes[i][1], 1);
		g_sig.new_stdout = cmd->pipes[i][1];
	}
	else if (size_tabcmd(cmd->cmd) > 1 && i != size_tabint(cmd->pipes))
		close(cmd->pipes[i][1]);
	else if (is_bi)
		g_sig.new_stdout = 1;
}

void	re_dup(t_cmd *cmd, int i)
{
	close_pipes(cmd, i);
	dup2(g_sig.old_stdin, 0);
	dup2(g_sig.old_stdout, 1);
}
