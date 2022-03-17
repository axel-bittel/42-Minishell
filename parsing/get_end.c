/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:23 by abittel           #+#    #+#             */
/*   Updated: 2022/03/17 19:49:39 by abittel          ###   ########.fr       */
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

int	get_end_arg(char *cmd, int start)
{
	int	i;

	i = start;
	while (cmd[++i])
	{
		if ((is_token(cmd[i]) == TOKEN_SPACE))
			return (i);
		else if (is_token(cmd[i]) != TOKEN_REST && \
is_token(cmd[i]) != TOKEN_ARG)
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
		&& is_token(cmd[i]) != TOKEN_ARG) || ((old_tok == TOKEN_SPACE) && \
		(is_token(cmd[i]) == TOKEN_ARG || is_token(cmd[i]) == TOKEN_REST)))
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
