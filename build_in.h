/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:19:32 by abittel           #+#    #+#             */
/*   Updated: 2022/02/25 20:25:40 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_IN_H
# define BUILD_IN_H
#include "libft.h"

int		cd_bi(t_list *env, char **cmd);
int		echo_bi(char **cmd, int fd);
int		pwd_bi(t_list *env, int fd);
int		env_bi(char **env, int fd);
int		export_bi(char **cmd, t_list *env);
int		is_absolute_path(char *cmd);
char	*get_absolute_path(t_list *env, char *path);
#endif
