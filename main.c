/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:32:19 by root              #+#    #+#             */
/*   Updated: 2022/03/17 19:53:12 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "exec_cmd.h"
#include "build_in.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

t_cmd	*parse_cmd(char *cmd, t_list *env)
{
	t_cmd_token	*res;
	t_tree		*final;
	int			i;

	i = -1;
	res = tokenisation(cmd);
	expander(res, env);
	final = parser(res, &i, 0);
	if (final)
	{
		g_sig.tree = final;
		exec_tree_cmd(final, env);
		free_tree(final);
	}
	else
		add_val(env, "?", "2", 0);
	free_cmd_token(res);
	return (0);
}

void	sig_sigint(int sig)
{
	if (sig == SIGINT)
		g_sig.stop_cmd = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_sigkill(int sig)
{
	(void)sig;
}

void	signal_catching(void)
{
	g_sig.run = 1;
	signal (SIGINT, &sig_sigint);
	signal (SIGQUIT, &sig_sigkill);
}

int	main(int argc, char **argv, char **envp)
{
	t_list			*env;
	char			*cmd;
	struct termios	attributes;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	signal_catching();
	env = get_fst_env(envp, argv[0]);
	while (g_sig.run)
	{
		rl_on_new_line ();
		cmd = readline("minishell > ");
		if (!cmd)
			exit_sig(1, env);
		if (!blank_cmd(cmd))
			add_history(cmd);
		parse_cmd (cmd, env);
		free (cmd);
	}
	return (0);
}
