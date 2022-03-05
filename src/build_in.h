/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:19:32 by abittel           #+#    #+#             */
/*   Updated: 2022/03/05 19:03:44 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_IN_H
# define BUILD_IN_H
# include "libft.h"
# include "parsing.h"

int		cd_bi(t_list *env, char **cmd);
int		echo_bi(char **cmd, int fd);
int		pwd_bi(t_list *env, int fd);
int		env_bi(char **env, int fd);
int		export_bi(char **cmd, t_list *env, int fd);
int		unset_bi(char **cmd, t_list *env);
int		is_absolute_path(char *cmd);
char	*get_absolute_path(t_list *env, char *path);
int		exit_bi(t_cmd *cmd, int i, int fd, t_list *env);
int		exit_sig(int exit_nb, t_list *env);
void	free_cmd(t_cmd *cmd);
#endif
