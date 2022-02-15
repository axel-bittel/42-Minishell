/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:58:53 by abittel           #+#    #+#             */
/*   Updated: 2022/02/15 10:17:42 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H
#include "libft.h"
typedef	struct s_env_var
{
	char	*name;
	char	*value;
}		t_env_var;
t_list	*get_fst_env(char **envp);
char	*ft_tabstrjoin(char **tab);
char	*get_val_var(t_list *lst, char *name);
void	add_val(t_list *lst, char *name, char *val);
char	**get_env_in_char(t_list *env);
#endif
