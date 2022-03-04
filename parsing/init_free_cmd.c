/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:56:15 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:18:18 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "parsing.h"
#include "exec_cmd.h"
#include "utils.h"
#include <unistd.h>

t_cmd	*init_cmd(void)
{
	t_cmd	*res;

	res = malloc (sizeof(t_cmd));
	res->cmd = malloc(sizeof(t_cmd *));
	res->cmd[0] = NULL;
	res->pipes = 0;
	return (res);
}

t_sub_cmd	*init_sub_cmd(void)
{
	t_sub_cmd	*res;

	res = malloc (sizeof(t_sub_cmd));
	res->cmd = 0;
	res->in = 0;
	res->fd_in = 0;
	res->hear_doc = 0;
	res->fd_hear_doc = 0;
	res->out_add = 0;
	res->fd_out_add = 0;
	res->out_replace = 0;
	res->fd_out_replace = 0;
	return (res);
}

void	free_cmd_token(t_cmd_token *cmd)
{
	free_tabstr(cmd->cmd);
	free_tabint(cmd->token);
	free(cmd);
}

t_tree	*free_tree(t_tree *tree)
{
	if (!tree)
		return (0);
	if (!tree->f_a && !tree->f_b)
		free_cmd((t_cmd *)tree->content);
	else
	{
		free((int *)tree->content);
		free_tree(tree->f_a);
		free_tree(tree->f_b);
	}
	free(tree);
	return (NULL);
}

int	idx_end_cmd(t_cmd_token *cmd, int idx)
{
	int	i;

	i = idx;
	while (cmd->cmd[++i])
	{
		if ((*cmd->token[i] == TOKEN_OR && !ft_strcmp(cmd->cmd[i], "||")) || \
	(*cmd->token[i] == TOKEN_AND && !ft_strcmp(cmd->cmd[i], "&&")) || \
*cmd->token[i] == TOKEN_BRACK_CL)
			return (i - 1);
	}
	return (i - 1);
}
