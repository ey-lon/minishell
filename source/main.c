/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/06/26 16:14:38 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sighandler(int signal)
{
	if (signal == CTRL_BS)
		;
	else if (signal == CTRL_D)
	{
		ft_putstr_fd("exit", 1);
		exit(0);
	}
	else if (signal == CTRL_C)
		ft_putstr_fd("\n$>", 1);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*cmd;
	t_list	*vars;
	t_msh	msh;

	msh.vars = &vars;
	msh.cmd = &cmd;
	(void)ac;
	(void)av;

	msh.exit = 0;
	msh.std[0] = dup(0);
	msh.std[1] = dup(1);
	msh.fd[0] = -2;
	msh.fd[1] = -2;

	signal(CTRL_C, ft_sighandler);
	signal(CTRL_D, ft_sighandler);
	signal(CTRL_BS, ft_sighandler);
	vars = NULL;
	ft_clone_env(&vars, env);	
	while (!msh.exit)
	{
		cmd = NULL;
		str = readline("$>");
		if (!ft_check_cmd_err(str))
		{
			ft_parsing(&cmd, str, &vars);
			add_history(str);
			free(str);

			//stampa di controllo del parsing----------
			//ft_print_lst(cmd);
			//-----------------------------------------

			msh.exit = ft_pipes(&cmd, &msh);
			ft_free_cmdlst(&cmd);
		}
		else
		{
			add_history(str);
			free(str);
		}
	}
	ft_free_varslst(&vars);
	return (0);
}
