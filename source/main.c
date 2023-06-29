/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/06/29 09:58:11 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sighandler(int signal)
{
	if (signal == CTRL_C)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_init(t_msh *msh, t_list **vars, t_list **cmd, char **env)
{
	*vars = NULL;
	*cmd = NULL;
	ft_clone_env(vars, env);
	msh->vars = vars;
	msh->cmd = cmd;
	msh->exit = 0;
	msh->std[0] = dup(0);
	msh->std[1] = dup(1);
	msh->fd[0] = -2;
	msh->fd[1] = -2;
}

void	ft_loop(t_msh *msh)
{
	char	*str;

	while (!msh->exit)
	{
		signal(CTRL_C, ft_sighandler);
		signal(CTRL_BS, SIG_IGN);
		str = readline("$>");
		if (!str)
			break ;
		else if (!ft_check_cmd_err(str))
		{
			ft_parsing(msh->cmd, str, msh->vars);
			//ft_print_lst(cmd); //(stampa di prova)
			msh->exit = ft_pipes(msh->cmd, msh);
			ft_free_cmdlst(msh->cmd);
			*msh->cmd = NULL;
		}
		add_history(str);
		free(str);
	}
	ft_free_varslst(msh->vars);
}

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;
	t_list	*vars;
	t_msh	msh;

	(void)ac;
	(void)av;
	/* signal(CTRL_C, ft_sighandler);
	signal(CTRL_BS, SIG_IGN); */
	ft_init(&msh, &vars, &cmd, env);
	ft_loop(&msh);
	ft_putstr_fd("exit\n", 1);
	exit(msh.exit);
	return (0);
}
