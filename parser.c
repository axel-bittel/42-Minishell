/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 05:30:26 by abittel           #+#    #+#             */
/*   Updated: 2022/02/14 17:54:04 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "parsing.h"
#include "ft_tree.h"
#include <stdio.h>

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

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->cmd[++i])
	{
		j = -1;
		while (cmd->cmd[i][++j])
			printf("%s\n", cmd->cmd[i][j]);
		printf("\n");
	}
	i = -1;
	while (cmd->in && cmd->in[++i])
		printf("%s", cmd->in[i]);
	printf("\n------------------------\n");
	i = -1;
	while (cmd->out_add && cmd->out_add[++i])
		printf("%s", cmd->out_add[i]);
	printf("\n------------------------\n");
	i = -1;
	while (cmd->out_replace && cmd->out_replace[++i])
		printf("%s", cmd->out_replace[i]);
	printf("\n");
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
		printf("TREE B :\n");
		print_tree(tree->f_b);
	}
}

t_cmd	*free_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->cmd[++i])
	{
		j = -1;
		while (cmd->cmd[i][++j])
			free (cmd->cmd[i][j]);
		free(cmd->cmd[i]);
	}
	if (cmd->cmd)
		free(cmd->cmd);
	i = -1;
	while (cmd->in && cmd->in[++i])
		free(cmd->in[i]);
	if (cmd->in)
		free(cmd->in);
	i = -1;
	while (cmd->out_add && cmd->out_add[++i])
		free(cmd->out_add[i]);
	if (cmd->out_add)
		free(cmd->out_add);
	i = -1;
	while (cmd->out_replace && cmd->out_replace[++i])
		free(cmd->out_replace[i]);
	if (cmd->out_replace)
		free(cmd->out_replace);
	return (NULL);
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
	return (NULL);
}

int	print_parse_error(t_cmd_token *cmd, int idx)
{
	if (cmd->cmd[idx + 1])
		printf ("SH: parse error near %s\n",cmd->cmd[idx + 1]);
	else
		printf ("SH: parse error near \\n\n");
	return (0);
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

t_cmd	*get_cmd(t_cmd_token *cmd, int idx)
{
	t_cmd	*res;
	char	**inter;

	inter = 0;
	res = malloc (sizeof(t_cmd));
	res->cmd = 0;
	res->in = 0;
	res->out_replace = 0;
	res->out_add = 0;
	while (cmd->cmd[idx])
	{
		if (*cmd->token[idx] == TOKEN_INDIR && next_is_input(cmd, idx))
			res->in = ft_tabjoin(res->in, cmd->cmd[idx++ + 1]);
		else if (*cmd->token[idx] == TOKEN_DINDIR && next_is_input(cmd, idx))
			res->hear_doc = ft_tabjoin(res->hear_doc, cmd->cmd[idx++ + 1]);
		else if (*cmd->token[idx] == TOKEN_REDIR && next_is_input(cmd, idx))
			res->out_replace = ft_tabjoin(res->out_replace, cmd->cmd[idx++ + 1]);
		else if (*cmd->token[idx] == TOKEN_ARG)
			inter = ft_tabjoin(inter, cmd->cmd[idx]);
		else if (*cmd->token[idx] == TOKEN_DREDIR && next_is_input(cmd, idx))
			res->out_add = ft_tabjoin(res->out_add, cmd->cmd[idx++ + 1]);
		else if ((*cmd->token[idx] & TOKEN_REST) && idx && (*cmd->token[idx - 1] & TOKEN_REST))
			str_join_to_last(inter, cmd->cmd[idx]);
		else if (is_input(cmd, idx))
		{
			if (!inter)
				*cmd->token[idx] = TOKEN_CMD;
			inter = ft_tabjoin(inter, cmd->cmd[idx]);
		}
		else if (*cmd->token[idx] == TOKEN_PIPE && (next_is_input(cmd, idx) || next_is_token(cmd, idx, TOKEN_BRACK_OP)))
		{
			res->cmd = ft_tabtabjoin(res->cmd, inter);
			inter = 0;
		}
		else if (!is_input(cmd, idx) && !is_redir(cmd, idx) && ft_strcmp(cmd->cmd[idx], "|") && (next_is_input(cmd, idx) || next_is_token(cmd, idx, TOKEN_BRACK_OP)))
		{
			res->cmd = ft_tabtabjoin(res->cmd, inter);
			inter = 0;
			break ;
		}
		else if(*cmd->token[idx] == TOKEN_BRACK_CL)// || next_is_token(cmd, idx, TOKEN_BRACK_CL))
			break ;
		else 
			return ((print_parse_error(cmd, idx), NULL));
		idx++;
	}
	if (inter)
		res->cmd = ft_tabtabjoin(res->cmd, inter);
	return (res);
}

int	set_tree_cmd(t_cmd_token *cmd, int *i, t_tree **inter_a, t_tree **final)
{
	int		*op_inter;

	if (*final)
		ft_treeadd_f(*final, *inter_a, 0);
	else
		*final = *inter_a;
	if (cmd->token[*i] && ((*cmd->token[*i] == TOKEN_OR && \
!ft_strncmp(cmd->cmd[*i], "||", 2)) || (*cmd->token[*i] == TOKEN_AND && \
!ft_strncmp(cmd->cmd[*i], "&&", 2))))
	{
		if (*final)
			*inter_a = *final;
		op_inter = malloc(sizeof(int));
		if (*cmd->token[*i] == TOKEN_AND)
			*op_inter = OP_AND;
		else if (*cmd->token[*i] == TOKEN_OR)
			*op_inter = OP_OR;
		*final = ft_treenew(op_inter);
		ft_treeadd_f(*final, *inter_a, 1);
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
			set_tree_cmd(cmd, i, &inter_a, &final);
		}
		else
			return (print_parse_error(cmd, *i), free_tree(inter_a), free_tree(final), NULL);
	}
	return (final);
}
