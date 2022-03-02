/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:38:46 by abittel           #+#    #+#             */
/*   Updated: 2022/03/02 20:52:17 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->pipes)
		free_tabint(cmd->pipes);
	while (cmd->cmd && cmd->cmd[++i])
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
	if(cmd->cmd)
		free(cmd->cmd);
	if (cmd)
		free(cmd);
}

int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	exit_bi(t_cmd *cmd, int i, int fd, t_list *env)
{
	int	stat;

	stat = 2;
	free_env(env);
	ft_putstr_fd("exit\n", fd);
	if(size_tabstr(cmd->cmd[i]->cmd) == 1)
	{
		free_tree(g_sig.tree);
		exit(0);
	}
	else if(size_tabstr(cmd->cmd[i]->cmd) == 2)
	{
		if (is_number(cmd->cmd[i]->cmd[1]))
			stat = ft_atoi(cmd->cmd[i]->cmd[1]);
		else
			ft_putstr_fd("BISCUIT: exit: ERROR ARGUMENT\n", 2);
		if (stat > 256 || stat < 0)
			stat = stat % 256;
		free_cmd(cmd);
		exit (stat);
	}
	else
		ft_putstr_fd("BISCUIT: exit: ERROR ARGUMENT\n", 2);
	return (1);
}

int	exit_sig(int exit_nb, t_list *env)
{
	free_env(env);
	ft_putstr_fd("exit\n", 1);
	exit(exit_nb);
}
