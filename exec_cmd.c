/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/12 19:45:04 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_infile(t_cmd *cmd)
{

}

int	exec_cmd(t_cmd *cmd, t_list *env)
{
	
}

void	exec_tree_cmd(t_tree *cmd, t_list *env)
{
	if (cmd->f_a && cmd->f_b)
	{
		
		if (*(int *)(cmd->content) == OP_AND)
		if (*(int *)(cmd->content) == OP_OR)
	}
	else
	{
		return (exec_cmd ((t_cmd *)(cmd->content), env));
	}
}
