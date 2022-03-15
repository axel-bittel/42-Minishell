/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:37:09 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 13:35:51 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "parsing.h"

void		str_join_to_last(char **tab, char *str);
char		*ft_tabstrjoin(char **tab);
void		free_tabint(int **tab_int);
void		free_tabstr(char **tab_str);
int			size_tabint(int **str);
int			**ft_tabintjoin(int **tab, int *num);
int			size_tabcmd(t_sub_cmd **tab);
t_sub_cmd	**ft_cmdjoin(t_sub_cmd **cmd, t_sub_cmd *add);
char		**ft_tabstrtrim(char **tab);
int			size_tabstr(char **str);
int			size_tabtabstr(char ***str);
char		**ft_tabjoin(char **tab, char *str);
char		***ft_tabtabjoin(char ***tab, char **tab_add);
char		*ft_substrdup(char	*str, int start, int end);
int			nb_chr_in_str(char *str, char chr);
char		*insert_str(char *str, char *str_ins, int *deb, int end);
int			is_path(char *str);
char		get_deb_word(char *str, int i);
char		get_end_word(char *str, int i);
int			ft_isspace(char c);
int			blank_cmd(char *cmd);
int			blanck_tabcmd(char **cmd);
#endif
