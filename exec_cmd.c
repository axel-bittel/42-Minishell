/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:35 by abittel           #+#    #+#             */
/*   Updated: 2022/02/13 20:23:45 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_infile(t_cmd *cmd)
{

}

int	exec_cmd(t_cmd *cmd, char **env)
{
	check_infile(cmd);
	//FORKS
	//GET_RETURN RES OF FORKS
}

int	exec_tree_cmd(t_tree *cmd, t_list *env)
{
	int	res_a;
	int	res_b;

	if (cmd->f_a && cmd->f_b)
	{
		res_a = exec_tree_cmd(fa, env);
		if ((*(int *)(cmd->content) == OP_AND && !res_a) ||
|| (*(int *)(cmd->content) == OP_OR && res_a))
		{
			res_b = exec_cmd(f_b, env);
			return (res_b);
		}
		return (res_a);
	}
	else
	{
		return (exec_cmd ((t_cmd *)(cmd->content), get_env_in_char(env)));
	}
}
