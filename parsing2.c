/*A ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:32:19 by root              #+#    #+#             */
/*   Updated: 2022/02/13 20:19:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "build_in.h"
#include "env_manager.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>

t_sig	g_sig;

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
		print_tree(final);
	//cd_bi(env, ((t_cmd *)(final->content))->cmd[0]);
	return (0);
}
void	sig_sigint(int sig)
{
	if (sig == SIGINT)
		g_sig.stop_cmd = 1;
	rl_on_new_line ();
}

void	signal_catching(void)
{
	g_sig.run = 1;
	//signal (SIGINT, &sig_sigint);
	signal (SIGQUIT, NULL);
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
