/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:50:08 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:14:22 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include "exec_cmd.h"

int	is_input(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx] && ((*cmd->token[idx] & TOKEN_REST) || \
*cmd->token[idx] == TOKEN_DQUOTE || *cmd->token[idx] == TOKEN_QUOTE))
		return (1);
	return (0);
}

int	next_is_input(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx + 1] && is_input(cmd, idx + 1))
		return (1);
	return (0);
}

int	next_is_token(t_cmd_token *cmd, int idx, int token)
{
	if (cmd->cmd[idx + 1] && *cmd->token[idx + 1] == token)
		return (1);
	return (0);
}

int	is_op(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx] && ((*cmd->token[idx] == TOKEN_AND) || \
*cmd->token[idx] == TOKEN_OR))
		return (1);
	return (0);
}

int	is_redir(t_cmd_token *cmd, int idx)
{
	if (*cmd->cmd[idx] && (*cmd->token[idx] == TOKEN_INDIR || \
*cmd->token[idx] == TOKEN_REDIR || *cmd->token[idx] == TOKEN_DREDIR))
		return (1);
	return (0);
}
