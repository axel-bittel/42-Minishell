/*A ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:32:19 by root              #+#    #+#             */
/*   Updated: 2022/02/28 18:50:48 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "build_in.h"
#include "env_manager.h"
#include "exec_cmd.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <term.h>

t_cmd	*parse_cmd (char *cmd, t_list *env)
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
		add_val(env, "?", "2");
	free_cmd_token(res);
	return (0);
}
void	sig_sigint(int sig)
{
	if (sig == SIGINT)
		g_sig.stop_cmd = 1;
	write(1, "\n", 1);
	rl_replace_line("", 1);
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
	signal (SIGKILL, &sig_sigkill);
}

void	print_header ()
{
ft_putstr_fd("\n██████╗░██╗░██████╗░█████╗░██╗░░░██╗██╗████████╗  ░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n", 1);
ft_putstr_fd("██╔══██╗██║██╔════╝██╔══██╗██║░░░██║██║╚══██╔══╝  ██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n", 1); 
ft_putstr_fd("██████╦╝██║╚█████╗░██║░░╚═╝██║░░░██║██║░░░██║░░░  ╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n", 1);
ft_putstr_fd("██╔══██╗██║░╚═══██╗██║░░██╗██║░░░██║██║░░░██║░░░  ░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n", 1);
ft_putstr_fd("██████╦╝██║██████╔╝╚█████╔╝╚██████╔╝██║░░░██║░░░  ██████╔╝██║░░██║███████╗███████╗███████╗\n", 1);
ft_putstr_fd("╚═════╝░╚═╝╚═════╝░░╚════╝░░╚═════╝░╚═╝░░░╚═╝░░░  ╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n", 1);
ft_putstr_fd("-----------------------------------------------------------------------------------------\n\n\n\n", 1);
}
int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*cmd;

	(void)argc;
	(void)argv;
	signal_catching();
	env = get_fst_env(envp);
	print_header();
	while (g_sig.run)
	{
		rl_on_new_line ();
		cmd = readline("BISCUIT > ");
		if (!cmd)
			exit_sig(1, env);
		parse_cmd (cmd, env);
		if (g_sig.stop_cmd)
		{
			g_sig.stop_cmd = 0;
			continue ;
		}
		free (cmd);
	}
	return (0);
}
