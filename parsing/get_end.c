/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:23 by abittel           #+#    #+#             */
/*   Updated: 2022/03/17 17:53:36 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	get_idx_until_c(char *cmd, int start, char c)
{
	int	i;

	i = start;
	while (cmd[++i])
		if (cmd[i] == c)
			return (i);
	return (-1);
}

int	get_idx_until_c_and_space(char *cmd, int start, char c)
{
	int	i;

	i = get_idx_until_c(cmd, start, c);
	while (cmd[++i])
	{
		if (cmd[i] == ' ' && cmd[i + 1] != ' ')
			return (i);
		else if (cmd[i] != ' ')
			return (i - 1);
	}
	return (-1);
}

int	get_idx_until_new_tok(char *cmd, int start)
{
	int	i;
	int	old_tok;

	i = start;
	old_tok = is_token(cmd[i]);
	while (cmd[++i])
	{
		if ((is_token(cmd[i]) != TOKEN_REST && is_token(cmd[i]) != TOKEN_SPACE \
		&& is_token(cmd[i]) != TOKEN_ARG) || ((old_tok == TOKEN_SPACE) && (is_token(cmd[i]) == TOKEN_ARG || is_token(cmd[i]) == TOKEN_REST)))
			return (i - 1);
		old_tok = is_token(cmd[i]);
	}
	return (-1);
}

int	get_idx_until_diff_tok(char *cmd, int start, int token)
{
	int	i;

	i = start;
	while (cmd[++i])
		if (is_token(cmd[i]) != token)
			return (i - 1);
	return (-1);
}

int	get_end_tok(char *cmd, int i)
{
	int	tok;

	tok = is_token(cmd[i]);
	if ((tok == TOKEN_DQUOTE || tok == TOKEN_QUOTE) && \
	(get_idx_until_c_and_space(cmd, i, cmd[i]) != -1))
		return (get_idx_until_c_and_space(cmd, i, cmd[i]));
	else if ((tok == TOKEN_ARG) && \
	(get_idx_until_c(cmd, i, ' ') != -1))
		return (get_idx_until_c(cmd, i, ' '));
	else if ((tok == TOKEN_REDIR || tok == TOKEN_INDIR || \
tok == TOKEN_AND || tok == TOKEN_OR) && \
	(get_idx_until_diff_tok(cmd, i, is_token(cmd[i])) != -1))
		return (get_idx_until_diff_tok(cmd, i, is_token(cmd[i])));
	else if ((tok == TOKEN_REST && !i) && \
	(get_idx_until_diff_tok(cmd, i, TOKEN_REST) != -1))
		return (get_idx_until_diff_tok(cmd, i, TOKEN_REST));
	else if (tok == TOKEN_REST || tok == TOKEN_SPACE)
	{
		if (get_idx_until_new_tok(cmd, i) != -1)
			return (get_idx_until_new_tok(cmd, i));
	}
	else if (tok == TOKEN_BRACK_OP || tok == TOKEN_BRACK_CL)
		return (i);
	return (ft_strlen(cmd) - 1);
}
