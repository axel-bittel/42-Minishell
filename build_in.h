/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:19:32 by abittel           #+#    #+#             */
/*   Updated: 2022/02/21 20:27:41 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_IN_H
# define BUILD_IN_H
#include "libft.h"

int	cd_bi(t_list *env, char **cmd);
int	echo_bi(char **cmd);
int	pwd_bi(t_list *env);
int	env_bi(char **env);
int	export_bi(char **cmd, t_list *env);
int	is_absolute_path(char *cmd);
#endif
