/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 05:27:48 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:06:51 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "exec_cmd.h"
#include "utils.h"
#include "build_in.h"
#include "libft.h"
#include <dirent.h>

int	get_begin_word(char *cmd, int i)
{
	while (i >= 0 && (is_token(cmd[i]) != TOKEN_SPACE && cmd[i] != ' '))
		i--;
	return (i + 1);
}

char	*delete_chr_in_str(char *str, char chr)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	res = malloc(sizeof(char) * (ft_strlen(str) - nb_chr_in_str(str, chr) + 1));
	while (str[++i])
	{
		if (str[i] != chr)
			res[++j] = str[i];
	}
	res[(ft_strlen(str) - nb_chr_in_str(str, chr))] = 0;
	free(str);
	return (res);
}

void	expander(t_cmd_token *cmd, t_list *env)
{
	int		i;

	i = -1;
	while (++i < size_tabint(cmd->token))
	{
		if (*cmd->token[i] == TOKEN_DQUOTE || *cmd->token[i] == TOKEN_QUOTE)
		{
			if (*cmd->token[i] == TOKEN_DQUOTE)
				cmd->cmd[i] = delete_chr_in_str(cmd->cmd[i], '\"');
			if (*cmd->token[i] == TOKEN_QUOTE)
				cmd->cmd[i] = delete_chr_in_str(cmd->cmd[i], '\'');
		}
		if (*cmd->token[i] == TOKEN_REST || *cmd->token[i] == TOKEN_DQUOTE)
			expand_var(cmd->cmd + i, env);
		if (*cmd->token[i] == TOKEN_REST)
			expand_star(cmd->cmd + i, env);
		if (*cmd->token[i] == TOKEN_DQUOTE || *cmd->token[i] == TOKEN_QUOTE)
			*cmd->token[i] |= TOKEN_REST;
	}
}
