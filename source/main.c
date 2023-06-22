/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/06/22 09:50:58 by abettini         ###   ########.fr       */
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

	signal(CTRL_C, ft_sighandler);
	signal(CTRL_D, ft_sighandler);
	signal(CTRL_BS, ft_sighandler);

	vars = NULL;
	ft_clone_env(&vars, env);	
	while (1)
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

			ft_pipes(&cmd, &msh, 1);
			ft_free_cmdlst(&cmd);
		}
		else
		{
			add_history(str);
			free(str);
		}
	}
	return (0);
}
