/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 05:30:26 by abittel           #+#    #+#             */
/*   Updated: 2022/03/04 21:18:42 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "parsing.h"
#include "exec_cmd.h"
#include "ft_tree.h"
#include "build_in.h"
#include <unistd.h>

/*
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
			if (tree->f_b)
				print_tree(tree->f_b);
		}
	}
}
*/

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
		else if (*cmd->token[i] == TOKEN_OR && !ft_strcmp(cmd->cmd[i], "||"))
			*cmd->token[i] = TOKEN_OR;
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
		else if (*cmd->token[*i] == TOKEN_BRACK_OP && (next_is_input(cmd, *i) \
	|| next_is_token(cmd, *i, TOKEN_BRACK_OP)))
		{
			inter_a = parser(cmd, i, 1);
			if (!inter_a)
				return (NULL);
			while (cmd->cmd[*i - 1] && cmd->cmd[*i] && cmd->cmd[*i + 1] && *cmd->token[*i] != \
TOKEN_BRACK_CL)
				*i = idx_end_cmd(cmd, *i) + 1;
			set_tree_cmd(cmd, i, &inter_a, &final);
		}
		else
			return (print_parse_error(cmd, *i), free_tree(inter_a), \
free_tree(final), NULL);
	}
	return (final);
}