/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:16:47 by abittel           #+#    #+#             */
/*   Updated: 2022/03/15 16:51:55 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H
# include "libft.h"
# include "parsing.h"

typedef struct s_env_var
{
	char	*name;
	char	*value;
	char	is_export;
}		t_env_var;
int		is_build_in(char *str);
int		exec_tree_cmd(t_tree *cmd, t_list *env);
int		exec_build_in(t_cmd *cmd, t_list *env, int i, int fd);
int		is_error(char **cmd);
void	get_path(t_list *env, char **cmd, char **path);
int		cd_bi(t_list *env, char **cmd);
int		echo_bi(char **cmd, int fd);
int		env_bi(char **env, int fd);
t_list	*get_fst_env(char **envp, char *lunch);
char	*get_val_var(t_list *lst, char *name);
void	add_val(t_list *lst, char *name, char *val, int is_export);
int		delete_val(t_list **lst, char *name);
char	**get_env_in_char(t_list *env);
void	free_env_var(t_env_var *var);
void	ft_lst_add_back_var(t_list *lst, char *name, char *val, int is_export);
void	delete_elem(t_list **lst, t_list *inter, t_list *prec);
void	add_val_not_exist(t_list *lst, char *name, char *val, int is_export);
void	free_env(t_list *env);
int		exec_sys_cmd(char **args, t_list *envp);
int		exec_sub_cmd(t_cmd *cmd, int *i, t_list *env);
int		exec_cmd(t_cmd *cmd, t_list *env);
int		exec_tree_cmd(t_tree *cmd, t_list *env);
void	free_cmd(t_cmd *cmd);
int		exit_bi(t_cmd *cmd, int i, int fd, t_list *env);
int		exit_sig(int exit_nb, t_list *env);
int		export_bi(char **cmd, t_list *env, int fd);
int		is_absolute_path(char *cmd);
int		idx_end_word(char *str, int i);
void	add_file_in_path(char **str, char *add);
void	delete_file_in_path(char **str);
char	*get_absolute_path(t_list *env, char *path);
void	get_pipes(t_cmd *cmd);
void	wait_end_child(t_cmd *cmd, t_list *env, int *status);
void	close_pipes(t_cmd *cmd, int idx);
int		pwd_bi(t_list *env, int fd);
void	read_heardoc_addline(char *line, char **res, char **inter);
char	*read_heardoc(char *end);
char	*get_name_hd(int i);
int		read_heardocs(t_sub_cmd *cmd, t_list *env);
int		check_file(char **names, int ***fd_tab, int ARG);
void	dup_manager(t_cmd *cmd, int i, int is_bi);
void	re_dup(t_cmd *cmd, int i);
int		unset_bi(char **cmd, t_list *env);
void	free_cmd(t_cmd *cmd);
void	free_cmd_token(t_cmd_token *cmd);
t_tree	*free_tree(t_tree *tree);
int		is_path(char *str);
char	get_deb_word(char *str, int i);
char	get_end_word(char *str, int i);
void	create_base_env(t_list **res, char *lunch);
char	*get_pwd(t_list *env);
#endif
