/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:00:51 by abittel           #+#    #+#             */
/*   Updated: 2022/03/08 18:07:52 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "exec_cmd.h"
#include "utils.h"
#include "libft.h"

int	get_cond_elem_redir_token(t_cmd_token *cmd, int *idx, t_sub_cmd **inter)
{
	if (*cmd->token[*idx] == TOKEN_REDIR && next_is_input(cmd, *idx))
	{
		(*inter)->out_replace = ft_tabjoin((*inter)->out_replace, \
ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_add = 0;
	}
	else if (*cmd->token[*idx] == TOKEN_ARG)
		(*inter)->cmd = ft_tabjoin((*inter)->cmd, ft_strdup(cmd->cmd[*idx]));
	else if (*cmd->token[*idx] == TOKEN_DREDIR && next_is_input(cmd, *idx))
	{
		(*inter)->out_add = ft_tabjoin((*inter)->out_add, \
ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_add = 1;
	}
	else
		return (0);
	return (1);
}

int	get_cmd_cond_elem_token(t_cmd_token *cmd, int *idx, t_sub_cmd **inter)
{
	if (*cmd->token[*idx] == TOKEN_INDIR && next_is_input(cmd, *idx))
	{
		(*inter)->in = ft_tabjoin((*inter)->in, \
ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_in = 1;
	}
	else if (*cmd->token[*idx] == TOKEN_DINDIR && next_is_input(cmd, *idx))
	{
		(*inter)->hear_doc = ft_tabjoin((*inter)->hear_doc, \
ft_strdup(cmd->cmd[(*idx)++ + 1]));
		(*inter)->last_is_in = 0;
	}
	else if (get_cond_elem_redir_token(cmd, idx, inter))
		return (1);
	else
		return (0);
	return (1);
}

int	get_cmd_add_rest(t_cmd_token *cmd, int idx, t_cmd *res, t_sub_cmd **inter)
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
	else if (!is_input(cmd, idx) && !is_redir(cmd, idx) && is_op(cmd, idx) \
	&& (next_is_input(cmd, idx) || next_is_token(cmd, idx, TOKEN_BRACK_OP)))
	{
		res->cmd = ft_cmdjoin(res->cmd, *inter);
		*inter = init_sub_cmd();
		return (2);
	}
	else if (*cmd->token[idx] == TOKEN_BRACK_CL)
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
			inter_res = get_cmd_add_rest(cmd, idx, res, &inter);
			if (inter_res == 2)
				break ;
			else if (!inter_res)
				return ((print_parse_error(cmd, idx), NULL));
		}
		idx++;
	}
	if (inter->cmd || inter->in || inter->hear_doc || inter->out_add || \
	inter->out_replace)
		res->cmd = ft_cmdjoin(res->cmd, inter);
	else
		free(inter);
	return (res);
}

void	set_tree_cmd(t_cmd_token *cmd, int *i, t_tree **inter_a, t_tree **final)
{
	int		*op_inter;

	if (*final)
		ft_treeadd_f(*final, *inter_a, 0);
	else
		*final = *inter_a;
	if (cmd->token[*i - 1] && cmd->token[*i] && (*cmd->token[*i] == TOKEN_OR || \
*cmd->token[*i] == TOKEN_AND || *cmd->token[*i] == TOKEN_PIPE || \
	(*cmd->token[*i] == TOKEN_BRACK_CL && cmd->token[*i + 1])))
	{
		if (*final)
			*inter_a = *final;
		op_inter = malloc(sizeof(int));
		if (*cmd->token[*i] == TOKEN_BRACK_CL)
			(*i)++;
		if (*cmd->token[*i] == TOKEN_AND)
			*op_inter = OP_AND;
		else if (*cmd->token[*i] == TOKEN_OR)
			*op_inter = OP_OR;
		*final = ft_treenew(op_inter);
		ft_treeadd_f(*final, *inter_a, 1);
		if (*cmd->token[*i] == TOKEN_BRACK_CL)
			ft_treeadd_f(*final, 0, 0);
	}
}
