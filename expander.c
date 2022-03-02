/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 05:27:48 by abittel           #+#    #+#             */
/*   Updated: 2022/03/02 19:53:44 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "env_manager.h"
#include "libft.h"
#include <dirent.h>

char	*insert_str(char *str, char *str_ins, int *deb, int end)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = -1;
	j = -1;
	k = end;
	res = malloc (sizeof(char) * (ft_strlen(str_ins) + ft_strlen(str) - (*deb - end + 1) + 1));
	while (++i < *deb)
		res[i] = str[i];
	while (++j < (int)ft_strlen(str_ins))
		res[i + j] = str_ins[j];
	while (str[++k])
		res[i + j++] = str[k];
	res[i + j] = 0;
	*deb += ft_strlen(str_ins) - 1;
	free(str);
	free(str_ins);
	return (res);
}

int	get_end_VAR(char *cmd, int i)
{
	int	idx_dollard;
	int	idx_space;
	int	idx_slash;

	idx_space = get_idx_until_c(cmd, i, ' ');
	idx_dollard = get_idx_until_c(cmd, i, '$');
	idx_slash= get_idx_until_c(cmd, i, '/');
	if ((idx_dollard <= idx_space || idx_space == -1) && \
(idx_dollard <= idx_slash || idx_slash == -1) && idx_dollard != -1)
		return (idx_dollard - 1);
	else if (idx_space != -1 && (idx_space <= idx_slash || idx_slash == -1) \
&& (idx_space <= idx_dollard || idx_dollard == -1))
		return (idx_space - 1);
	else if (idx_slash != -1)
		return (idx_slash - 1);
	else
		return (ft_strlen(cmd) - 1);
}

void	expand_VAR(char **cmd, t_list *env)
{
	int		i;
	char	*inter;

	i = -1;
	while (++i < (int)ft_strlen(*cmd) && (*cmd)[i])
	{
		if ((*cmd)[i] == '$')
		{
			inter = ft_substrdup(*cmd, i + 1, get_end_VAR(*cmd, i));
			*cmd = insert_str(*cmd, ft_strdup(get_val_var(env, inter)), &i, get_end_VAR(*cmd, i));
			free (inter);
		}
	}
}

int	get_begin_word(char *cmd, int i)
{
	while (i >= 0 && (is_token(cmd[i]) != TOKEN_SPACE && cmd[i] != ' '))
		i--;
	return (i + 1);
}

int	is_correspond(char *str, char *corres)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] && corres[j])
	{
		if ((corres[j] == '*' && str[i] == corres[j + 1]))
			j += 2;
		else if (corres[j] != '*' && corres[j] == str[i])
			j++;
		else if (corres[j] != '*' && corres[j] != str[i])
			return (0);
	}
	if (!corres[j] ||  (corres[j] == '*' && !corres[j + 1]))
		return (1);
	else
		return (0);
}

char	*get_corespond_words(t_list *env, char *corres)
{
	char			*res;
	char			*inter;
	struct dirent	*f_read;
	DIR				*folder;

	res = malloc (sizeof(char));
	res[0] = 0;
	folder = opendir(get_val_var(env, "PWD"));
	f_read = readdir(folder);
	while (f_read)
	{
		if (is_correspond(f_read->d_name, corres))
		{
			inter = res;
			res = ft_strjoin(res, " ");
			free(inter);
			inter = res;
			res = ft_strjoin(res, f_read->d_name);
			free(inter);
		}
		f_read = readdir(folder);
	}
	return (res);
}

void	expand_star(char **cmd, t_list *env)
{
	int		i;
	int		end_w;
	char	*inter;

	i = -1;
	while (++i < (int)ft_strlen(*cmd) && (*cmd)[i])
	{
		if((*cmd)[i] == '*')
		{
			end_w = get_idx_until_c(*cmd, i, ' '); 
			if (end_w == -1)
				end_w = ft_strlen(*cmd) - 1;
			inter = ft_substrdup(*cmd, get_begin_word(*cmd, i), get_end_VAR(*cmd, i));
			i = get_begin_word(*cmd, i);
			*cmd = insert_str(*cmd, get_corespond_words(env, inter), &i, get_end_VAR(*cmd, i));
		}
	}
}

int	nb_chr_in_str(char *str, char chr)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] == chr)
			res++;
	return (res);
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
			expand_VAR(cmd->cmd + i, env);
		if (*cmd->token[i] == TOKEN_REST)
			expand_star(cmd->cmd + i, env);
		if (*cmd->token[i] == TOKEN_DQUOTE || *cmd->token[i] == TOKEN_QUOTE)
			*cmd->token[i] |= TOKEN_REST;
	}
}
