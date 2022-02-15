/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:37:22 by abittel           #+#    #+#             */
/*   Updated: 2022/02/15 10:17:13 by abittel          ###   ########.fr       */
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
# include "ft_tree.h"
# include "libft.h"

typedef struct s_cmd_token
{
	char			**cmd;
	int				**token;
}				t_cmd_token;

typedef struct s_cmd
{
	char			***cmd;
	char			**in;
	char			**hear_doc;
	char			**out_add;
	char			**out_replace;
}				t_cmd;

typedef struct s_sig
{
	int	run;
	int	stop_cmd;
}	t_sig;

int			is_token (char c);
int			get_idx_until_c(char *cmd, int start, char c);
int			get_idx_until_new_tok(char *cmd, int start);
int			get_end_tok(char *cmd, int i);
t_cmd_token	*tokenisation(char *cmd);
char		*ft_substrdup(char	*str, int start, int end);
int			**ft_tabintjoin(int **tab, int* num);
char		**ft_tabjoin(char **tab, char *str);
void		free_tabstr(char **tab_str);
int			size_tabint(int **str);
int			size_tabstr(char **str);
t_tree		*parser(t_cmd_token *cmd, int *i, int is_sub);
char		***ft_tabtabjoin(char ***tab, char **tab_add);
void		print_tree(t_tree *tree);
void		expander(t_cmd_token *cmd, t_list *env);
void		free_tabstr(char **tab_str);
#endif
