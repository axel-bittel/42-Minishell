/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 05:30:26 by abittel           #+#    #+#             */
/*   Updated: 2022/03/01 21:12:20 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "parsing.h"
#include "ft_tree.h"
#include "build_in.h"
#include <unistd.h>

int	idx_end_cmd(t_cmd_token *cmd, int idx)
{
	int	i;

	i = idx;
	while (cmd->cmd[++i])
	{
		if ((*cmd->token[i] == TOKEN_OR && !ft_strncmp(cmd->cmd[i], "||", 2)) \
|| (*cmd->token[i] == TOKEN_AND && !ft_strncmp(cmd->cmd[i], "&&", 2)) || \
*cmd->token[i] == TOKEN_BRACK_CL)
			return (i - 1);
	}
	return (i - 1);
}

int	is_input(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx] && ((*cmd->token[idx] & TOKEN_REST) || \
*cmd->token[idx] == TOKEN_DQUOTE || *cmd->token[idx] == TOKEN_QUOTE))
		return (1);
	return (0);
}

int	is_op(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx] && ((*cmd->token[idx] == TOKEN_AND) || \
*cmd->token[idx] == TOKEN_PIPE || *cmd->token[idx] == TOKEN_OR))
		return (1);
	return (0);
}

int	is_redir(t_cmd_token *cmd, int idx)
{
	if (*cmd->cmd[idx] && (*cmd->token[idx] == TOKEN_INDIR || \
*cmd->token[idx] == TOKEN_REDIR || *cmd->token[idx] == TOKEN_DREDIR))
		return (1);
	return (0);
}
void	str_join_to_last(char **tab, char *str)
{
	char	*inter;

	inter = tab[size_tabstr(tab) - 1];
	tab[size_tabstr(tab) - 1] = ft_strjoin(tab[size_tabstr(tab) - 1], str);
	free(inter);
}
#include <stdio.h>
void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->cmd[++i])
	{
		j = -1;
		while (cmd->cmd[i]->cmd && cmd->cmd[i]->cmd[++j])
			printf("%s\n", cmd->cmd[i]->cmd[j]);
		printf("\n");
		j = -1;
		while (cmd->cmd[i]->in && cmd->cmd[i]->in[++j])
			printf("%s", cmd->cmd[i]->in[j]);
		printf("\n------------------------\n");
		j = -1;
		while (cmd->cmd[i]->out_add && cmd->cmd[i]->out_add[++j])
			printf("%s", cmd->cmd[i]->out_add[j]);
		printf("\n------------------------\n");
		j = -1;
		while (cmd->cmd[i]->out_replace && cmd->cmd[i]->out_replace[++j])
			printf("%s", cmd->cmd[i]->out_replace[j]);
		printf("\n*************************************\n");
	}
}

void	print_tree(t_tree *tree)
{
	if (!tree->f_a && !tree->f_b)
		print_cmd((t_cmd *)tree->content);
	else
	{
		printf("TREE A :\n");
		print_tree(tree->f_a);
		if (*(int *)tree->content == OP_OR)
			printf("||\n");
		else if (*(int *)tree->content == OP_AND)
			printf("&&\n");
		else if (*(int *)tree->content == OP_PIPE)
			printf("|\n");
		else if (*(int *)tree->content == OP_BRACK)
			printf("()\n");
		if (*(int *)tree->content != OP_BRACK)
		{
			printf("TREE B :\n");
			print_tree(tree->f_b);
		}
	}
}


void	free_cmd_token(t_cmd_token *cmd)
{
	free_tabstr(cmd->cmd);
	free_tabint(cmd->token);
	free(cmd);
}

t_tree	*free_tree(t_tree *tree)
{
	if (!tree)
		return (0);
	if (!tree->f_a && !tree->f_b)
		free_cmd((t_cmd *)tree->content);
	else
	{
		free((int *)tree->content);
		free_tree(tree->f_a);
		free_tree(tree->f_b);
	}
	free(tree);
	return (NULL);
}

int	print_parse_error(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx + 1])
	{
		ft_putstr_fd("SH: parse error near ", 2);
		ft_putstr_fd(cmd->cmd[idx + 1], 2);
		write (2, "\n", 1);
	}
	else
		ft_putstr_fd("SH: parse error near \n", 2);
	return (1);
}

int	next_is_input(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx + 1] && is_input(cmd, idx + 1))
		return (1);
	return (0);
}

int	next_is_token(t_cmd_token *cmd, int idx, int token)
{
	if (cmd->cmd[idx + 1] && *cmd->token[idx + 1] == token)
		return (1);
	return (0);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*res;

	res = malloc (sizeof(t_cmd));
	res->cmd = malloc(sizeof(t_cmd *));
	res->cmd[0] = NULL;
	res->pipes = 0;
	return (res);
}

t_sub_cmd	*init_sub_cmd(void)
{
	t_sub_cmd	*res;

	res = malloc (sizeof(t_sub_cmd));
	res->cmd = 0;
	res->in= 0;
	res->fd_in = 0;
	res->hear_doc = 0;
	res->fd_hear_doc = 0;
	res->out_add = 0;
	res->fd_out_add = 0;
	res->out_replace = 0;
	res->fd_out_replace = 0;
	return (res);
}

int	get_cmd_cond_elem_token(t_cmd_token *cmd, int *idx, t_sub_cmd **inter)
{
	if (*cmd->token[*idx] == TOKEN_INDIR && next_is_input(cmd, *idx))
	{
		(*inter)->in = ft_tabjoin((*inter)->in, ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_in = 1;
	}
	else if (*cmd->token[*idx] == TOKEN_DINDIR && next_is_input(cmd, *idx))
	{
		(*inter)->hear_doc = ft_tabjoin((*inter)->hear_doc, ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_in = 0;
	}
	else if (*cmd->token[*idx] == TOKEN_REDIR && next_is_input(cmd, *idx))
	{
		(*inter)->out_replace = ft_tabjoin((*inter)->out_replace, ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_add = 0;
	}
	else if (*cmd->token[*idx] == TOKEN_ARG)
		(*inter)->cmd = ft_tabjoin((*inter)->cmd, ft_strdup(cmd->cmd[*idx]));
	else if (*cmd->token[*idx] == TOKEN_DREDIR && next_is_input(cmd, *idx))
	{
		(*inter)->out_add = ft_tabjoin((*inter)->out_add, ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_add = 1;
	}
	else
		return (0);
	return (1);
}

int	get_cmd_cond_add_rest(t_cmd_token *cmd, int idx, t_cmd *res, t_sub_cmd **inter)
{
	if (is_input(cmd, idx))
	{
		if (!(*inter)->cmd)
			*cmd->token[idx] = TOKEN_CMD;
		(*inter)->cmd = ft_tabjoin((*inter)->cmd, ft_strdup(cmd->cmd[idx]));
	}
	else if (*cmd->token[idx] == TOKEN_PIPE && (next_is_input(cmd, idx) \
|| next_is_token(cmd, idx, TOKEN_BRACK_OP)))
	{
		res->cmd = ft_cmdjoin(res->cmd, *inter);
		*inter = init_sub_cmd();
	}
	else if (!is_input(cmd, idx) && !is_redir(cmd, idx) && is_op(cmd, idx) &&\
(next_is_input(cmd, idx) || next_is_token(cmd, idx, TOKEN_BRACK_OP)))
	{
		res->cmd = ft_cmdjoin(res->cmd, *inter);
		*inter = init_sub_cmd();
		return (2);
	}
	else if(*cmd->token[idx] == TOKEN_BRACK_CL)
		return (2);
	else
		return (0);
	return (1);
}

t_cmd	*get_cmd(t_cmd_token *cmd, int idx)
{
	t_cmd		*res;
	t_sub_cmd	*inter;
	int			inter_res;

	inter = 0;
	res = init_cmd();
	inter = init_sub_cmd();
	while (cmd->cmd[idx])
	{
		if (!get_cmd_cond_elem_token(cmd, &idx, &inter))
		{
			inter_res = get_cmd_cond_add_rest(cmd, idx, res, &inter);
			if(inter_res == 2)
				break ;
			else if(!inter_res)
				return ((print_parse_error(cmd, idx), NULL));
		}
		idx++;
	}
	if (inter)
		res->cmd = ft_cmdjoin(res->cmd, inter);
	else
		free(inter);
	return (res);
}

int	set_tree_cmd(t_cmd_token *cmd, int *i, t_tree **inter_a, t_tree **final)
{
	int		*op_inter;

	if (*final)
		ft_treeadd_f(*final, *inter_a, 0);
	else
		*final = *inter_a;
	if (cmd->token[*i] && (*cmd->token[*i] == TOKEN_OR || \
*cmd->token[*i] == TOKEN_AND || *cmd->token[*i] == TOKEN_PIPE || \
(*cmd->token[*i] == TOKEN_BRACK_CL && *cmd->token[*i - 1] == TOKEN_BRACK_CL)))
	{
		if (*final)
			*inter_a = *final;
		op_inter = malloc(sizeof(int));
		if (*cmd->token[*i] == TOKEN_AND)
			*op_inter = OP_AND;
		else if (*cmd->token[*i] == TOKEN_OR)
			*op_inter = OP_OR;
		else if (*cmd->token[*i] == TOKEN_PIPE)
			*op_inter = OP_PIPE;
		else if (*cmd->token[*i] == TOKEN_BRACK_CL && *cmd->token[*i - 1] == TOKEN_BRACK_CL)
			*op_inter = OP_BRACK;
		*final = ft_treenew(op_inter);
		ft_treeadd_f(*final, *inter_a, 1);
		if (*cmd->token[*i] == TOKEN_BRACK_CL)
			ft_treeadd_f(*final, 0, 0);
	}
	return (1);
}

int	get_tree_cmd(t_cmd_token *cmd, int *i, t_tree **inter_a, t_tree **final)
{

	*inter_a = ft_treenew((void *)get_cmd(cmd, *i));
	if ((*inter_a) == NULL)
		return (0);
	*i = idx_end_cmd(cmd, *i) + 1;
	set_tree_cmd(cmd, i, inter_a, final);
	if (!cmd->cmd[*i])
		(*i)--;
	return (1);
}

void	set_up_tok(t_cmd_token *cmd)
{
	int	i;

	i = -1;
	while (++i < size_tabint(cmd->token))
	{
		if (*cmd->token[i] == TOKEN_OR && !ft_strcmp(cmd->cmd[i], "|"))
			*cmd->token[i] = TOKEN_PIPE;
		else if (*cmd->token[i] == TOKEN_REDIR && !ft_strcmp(cmd->cmd[i], ">>"))
			*cmd->token[i] = TOKEN_DREDIR;
		else if (*cmd->token[i] == TOKEN_INDIR && !ft_strcmp(cmd->cmd[i], "<<"))
			*cmd->token[i] = TOKEN_DINDIR;
	}

}

t_tree	*parser(t_cmd_token *cmd, int *i, int is_sub)
{
	t_tree	*inter_a;
	t_tree	*final;

	inter_a = 0;
	final = 0;
	set_up_tok(cmd);
	while (++(*i) < size_tabint(cmd->token))
	{
		if (*i && *cmd->token[*i - 1] == TOKEN_BRACK_CL && is_sub)
			return (final);
		else if (*i && *cmd->token[*i] == TOKEN_BRACK_CL && !is_sub)
			return (free_tree(final), (print_parse_error(cmd, *i), NULL));
		else if (*cmd->token[*i] != TOKEN_BRACK_OP)
		{
			if (!get_tree_cmd(cmd, i, &inter_a, &final))
				return (free_tree(inter_a), free_tree(final), NULL);
		}
		else if (*cmd->token[*i] == TOKEN_BRACK_OP && (next_is_input(cmd, *i) || next_is_token(cmd, *i, TOKEN_BRACK_OP)))
		{
			inter_a = parser(cmd, i, 1);
			if (!inter_a)
				return (NULL);
			while (cmd->cmd[*i] && cmd->cmd[*i + 1] && *cmd->token[*i - 1] != TOKEN_BRACK_CL)
				*i = idx_end_cmd(cmd, *i) + 1;
			if (is_sub)
				set_tree_cmd(cmd, i, &inter_a, &final);
			else
				final = inter_a;
		}
		else
			return (print_parse_error(cmd, *i), free_tree(inter_a), free_tree(final), NULL);
	}
	return (final);
}
