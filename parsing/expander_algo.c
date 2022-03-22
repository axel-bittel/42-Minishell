/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:06:26 by abittel           #+#    #+#             */
/*   Updated: 2022/03/22 23:34:35 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "parsing.h"
#include "exec_cmd.h"
#include "utils.h"

int	get_end_var(char *cmd, int i)
{
	int	idx_dollard;
	int	idx_space;
	int	idx_slash;

	idx_space = get_idx_until_c(cmd, i, ' ');
	idx_dollard = get_idx_until_c(cmd, i, '$');
	idx_slash = get_idx_until_c(cmd, i, '/');
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

void	expand_var(char **cmd, t_list *env)
{
	int		i;
	char	*inter;
	char	*val;

	i = -1;
	while (++i < (int)ft_strlen(*cmd) && (*cmd)[i])
	{
		if ((*cmd)[i] == '$')
		{
			inter = ft_substrdup(*cmd, i + 1, get_end_var(*cmd, i));
			val = get_val_var(env, inter);
			*cmd = insert_str(*cmd, ft_strdup(val), &i, \
get_end_var(*cmd, i));
			if (!val[0])
				free(val);
			free (inter);
		}
	}
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
	if (!corres[j] || (corres[j] == '*' && !corres[j + 1]))
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
			if (res[0])
				res = ft_strjoin(res, " ");
			if (res[0])
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
		if ((*cmd)[i] == '*')
		{
			end_w = get_idx_until_c(*cmd, i, ' ');
			if (end_w == -1)
				end_w = ft_strlen(*cmd) - 1;
			inter = ft_substrdup(*cmd, get_begin_word(*cmd, i), \
get_end_var(*cmd, i));
			i = get_begin_word(*cmd, i);
			*cmd = insert_str(*cmd, get_corespond_words(env, inter), &i, \
get_end_var(*cmd, i));
		}
	}
}
