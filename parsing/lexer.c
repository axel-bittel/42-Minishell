/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:32:06 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 17:48:59 by abittel          ###   ########.fr       */
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
