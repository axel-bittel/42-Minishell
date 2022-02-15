/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:52:24 by abittel           #+#    #+#             */
/*   Updated: 2022/02/14 17:40:00 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

int	is_token (char c)
{
	if (c == '-')
		return (TOKEN_ARG);
	else if (c == '\'')
		return (TOKEN_QUOTE);
	else if (c == '\"')
		return (TOKEN_DQUOTE);
	else if (c == '>')
		return (TOKEN_REDIR);
	else if (c == '<')
		return (TOKEN_INDIR);
	else if (c == ' ')
		return (TOKEN_SPACE);
	else if (c == '&')
		return (TOKEN_AND);
	else if (c == '|')
		return (TOKEN_OR);
	else if (c == '(')
		return (TOKEN_BRACK_OP);
	else if (c == ')')
		return (TOKEN_BRACK_CL);
	return (TOKEN_REST);
}

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
		else if(cmd[i] != ' ')
			return (i - 1);
	}
	return (-1);
}

int	get_idx_until_new_tok(char *cmd, int start)
{
	int	i;

	i = start;
	while (cmd[++i])
		if (is_token(cmd[i]) != TOKEN_REST && is_token(cmd[i]) != TOKEN_SPACE)
			return (i - 1);
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
	if (tok == TOKEN_DQUOTE || tok == TOKEN_QUOTE)
	{
		if (get_idx_until_c_and_space(cmd, i, cmd[i]) != -1)
			return (get_idx_until_c_and_space(cmd, i, cmd[i]));
	}
	else if (tok == TOKEN_ARG)
	{
		if (get_idx_until_diff_tok(cmd, i, TOKEN_REST) != -1)
			return (get_idx_until_diff_tok(cmd, i, TOKEN_REST));
	}
	else if (tok == TOKEN_REDIR || tok == TOKEN_INDIR || \
tok == TOKEN_AND || tok == TOKEN_OR)
	{
		if (get_idx_until_diff_tok(cmd, i, is_token(cmd[i])) != -1)
			return (get_idx_until_diff_tok(cmd, i, is_token(cmd[i])));
	}
	else if (tok == TOKEN_REST && !i)
	{
		if (get_idx_until_diff_tok(cmd, i, TOKEN_REST) != -1)
			return (get_idx_until_diff_tok(cmd, i, TOKEN_REST));
	}
	else if (tok == TOKEN_REST || tok == TOKEN_SPACE)
	{
		if (get_idx_until_new_tok(cmd, i) != -1)
			return (get_idx_until_new_tok(cmd, i));
	}
	else if (tok == TOKEN_BRACK_OP || tok == TOKEN_BRACK_CL)
		return (i);
	return (ft_strlen(cmd) - 1);
}

t_cmd_token	*tokenisation(char *cmd)
{
	int			i;
	int			*inter;
	char		*cmd_int;
	t_cmd_token	*tok;

	i = -1;
	tok = malloc (sizeof (t_cmd_token));
	tok->token = 0;
	tok->cmd = 0;
	cmd_int = ft_strtrim(cmd, " ");
	while (cmd_int[++i])
	{
		if (is_token(cmd_int[i]) != TOKEN_SPACE)
		{
			inter = malloc (sizeof(int));
			*inter = is_token(cmd_int[i]);
			tok->cmd = ft_tabjoin(tok->cmd, ft_substrdup(cmd, i, get_end_tok(cmd_int, i)));
			tok->token = ft_tabintjoin(tok->token, inter);
			i = get_end_tok(cmd_int, i);
		}
	}
	return (tok);
}
