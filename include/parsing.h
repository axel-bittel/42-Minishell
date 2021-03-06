/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:37:22 by abittel           #+#    #+#             */
/*   Updated: 2022/03/19 23:05:45 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define TOKEN_ARG 1
# define TOKEN_QUOTE 2
# define TOKEN_DQUOTE 4
# define TOKEN_REST 8
# define TOKEN_REDIR 16
# define TOKEN_DREDIR 32
# define TOKEN_INDIR 64
# define TOKEN_DINDIR 128
# define TOKEN_SPACE 256
# define TOKEN_AND 512
# define TOKEN_OR 1024
# define TOKEN_BRACK_OP 2048
# define TOKEN_BRACK_CL 4096
# define TOKEN_CMD 8192 
# define TOKEN_PIPE 16384 
# define OP_AND 1
# define OP_OR 2
# define OP_PIPE 3
# define OP_BRACK 4
# include "ft_tree.h"
# include "libft.h"

typedef struct s_cmd_token
{
	char			**cmd;
	int				**token;
}				t_cmd_token;

typedef struct s_sub_cmd
{
	char	**cmd;
	char	**in;
	int		**fd_in;
	char	**hear_doc;
	int		**fd_hear_doc;
	char	**out_add;
	int		**fd_out_add;
	char	**out_replace;
	int		**fd_out_replace;
	int		last_is_add;
	int		last_is_in;
	int		**token;
}			t_sub_cmd;

typedef struct s_cmd
{
	t_sub_cmd	**cmd;
	int			**pipes;
}				t_cmd;

typedef struct s_sig
{
	int			run;
	int			stop_cmd;
	int			old_stdin;
	int			old_stdout;
	int			new_stdin;
	int			new_stdout;
	t_tree		*tree;
}	t_sig;

t_sig	g_sig;

int			is_token(char c);
int			is_input(t_cmd_token *cmd, int idx);
int			next_is_input(t_cmd_token *cmd, int idx);
int			next_is_token(t_cmd_token *cmd, int idx, int token);
int			get_idx_until_c(char *cmd, int start, char c);
int			get_idx_until_new_tok(char *cmd, int start);
int			get_end_tok(char *cmd, int i);
int			is_op(t_cmd_token *cmd, int idx);
int			is_redir(t_cmd_token *cmd, int idx);
t_cmd_token	*tokenisation(char *cmd);
char		*ft_substrdup(char	*str, int start, int end);
int			**ft_tabintjoin(int **tab, int *num);
char		**ft_tabjoin(char **tab, char *str);
void		free_tabstr(char **tab_str);
void		free_tabint(int **tab_int);
int			size_tabint(int **str);
int			size_tabstr(char **str);
int			size_tabtabstr(char ***str);
t_tree		*parser(t_cmd_token *cmd, int *i, int is_sub);
char		***ft_tabtabjoin(char ***tab, char **tab_add);
t_sub_cmd	**ft_cmdjoin(t_sub_cmd **cmd, t_sub_cmd *add);
void		print_tree(t_tree *tree);
void		expander(t_cmd_token *cmd, t_list *env);
void		free_tabstr(char **tab_str);
int			size_tabcmd(t_sub_cmd **tab);
char		*ft_tabstrjoin(char **tab);
char		**ft_tabstrtrim(char **tab);
void		expand_var(char **cmd, t_list *env);
void		expand_star(char **cmd, t_list *env);
int			print_parse_error(t_cmd_token *cmd, int idx);
int			get_begin_word(char *cmd, int i);
t_cmd		*init_cmd(void);
t_sub_cmd	*init_sub_cmd(void);
t_cmd		*get_cmd(t_cmd_token *cmd, int idx);
int			idx_end_cmd(t_cmd_token *cmd, int idx);
void		set_tree_cmd(t_cmd_token *cmd, int *i, t_tree **inter_a, \
t_tree **final);
void		env_export(t_list *lst, int fd);
int			get_idx_until_c(char *cmd, int start, char c);
int			get_idx_until_c_and_space(char *cmd, int start, char c);
int			get_end_arg(char *cmd, int start);
int			get_idx_until_new_tok(char *cmd, int start);
int			get_idx_until_diff_tok(char *cmd, int start, int token);
#endif
