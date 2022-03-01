/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:00:42 by itaouil           #+#    #+#             */
/*   Updated: 2021/11/30 12:00:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_pathlist(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])))
			i++;
		else
			return (ft_split(ft_strtrim(envp[i], "PATH="), ':'));
	}
	return (NULL);
}

static char	*get_flags(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != ' ')
		i++;
	if (!argv[i])
		return (NULL);
	i++;
	return (ft_strdup(argv + i));
}

static char	*trim_command(char *command)
{
	int		i;
	int		j;
	char	*cmd_without_flags;

	i = 0;
	while (command[i] && command[i] != ' ')
		i++;
	cmd_without_flags = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		cmd_without_flags[j] = command[j];
		j++;
	}
	cmd_without_flags[j] = 0;
	return (cmd_without_flags);
}

char	*get_pathname(char **envp, char *argv)
{
	int		i;
	char	**pathlist;
	char	*path_to_try;
	char	*cmd;
	char	*arg;

	i = 0;
	pathlist = get_pathlist(envp);
	cmd = trim_command(argv);
	arg = ft_strjoin("/", cmd);
	free(cmd);
	while (pathlist && pathlist[i])
	{
		path_to_try = ft_strjoin(pathlist[i], arg);
		if (!access(path_to_try, F_OK))
		{
			free(arg);
			return (path_to_try);
		}
		i++;
		free(path_to_try);
	}
	free(pathlist);
	free(arg);
	return (NULL);
}

char	**get_execve_list(char **envp, char *command)
{

	char	*pathname;
	char	*list_str;
	char	*flags;
	char	*tmp;

	pathname = get_pathname(envp, command);
	tmp = ft_strjoin(pathname, " ");
	if (!get_flags(command))
		return (ft_split(tmp, ' '));
	else
	{
		flags = ft_strjoin(get_flags(command), " ");
		list_str = ft_strjoin(tmp, flags);
		free(tmp);
		free(flags);
		return (ft_split(list_str, ' '));
	}
}
