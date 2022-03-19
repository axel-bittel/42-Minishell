/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:32:06 by abittel           #+#    #+#             */
/*   Updated: 2022/03/19 22:34:14 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

int	is_token(char c)
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

int	get_end_tok(char *cmd, int i)
{
	int	tok;

	tok = is_token(cmd[i]);
	if ((tok == TOKEN_DQUOTE || tok == TOKEN_QUOTE) && \
	(get_idx_until_c_and_space(cmd, i, cmd[i]) != -1))
		return (get_idx_until_c_and_space(cmd, i, cmd[i]));
	else if ((tok == TOKEN_ARG) && \
	(get_end_arg(cmd, i) != -1))
		return (get_end_arg(cmd, i));
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
	if (cmd)
		cmd_int = ft_strtrim(cmd, " ");
	while (cmd && cmd_int[++i])
	{
		if (is_token(cmd_int[i]) != TOKEN_SPACE)
		{
			inter = malloc (sizeof(int));
			*inter = is_token(cmd_int[i]);
			tok->cmd = ft_tabjoin(tok->cmd, ft_substrdup(cmd, i, \
get_end_tok(cmd_int, i)));
			tok->token = ft_tabintjoin(tok->token, inter);
			i = get_end_tok(cmd_int, i);
		}
	}
	free(cmd_int);
	return (tok);
}
