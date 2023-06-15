/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/06/15 14:49:58 by abettini         ###   ########.fr       */
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

//-------------------------------------------------------
//funzione per creare dei nodi nella lista di variabili
//(usata per testare)
void	ft_vars_ex(t_list **vars)
{
	t_var	*new;

	new = malloc(sizeof(t_var) * 1);
	new->name = ft_strdup("VAR1");
	new->value = ft_strdup("cho");
	new->exp = 0;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
	new = malloc(sizeof(t_var) * 1);
	new->name = ft_strdup("VAR2");
	new->value = ft_strdup("banana");
	new->exp = 1;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
	new = malloc(sizeof(t_var) * 1);
	new->name = ft_strdup("VAR11");
	new->value = ft_strdup("test");
	new->exp = 2;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
}
//-------------------------------------------------------

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*cmd;
	t_list	*vars;

	ac = ac;
	av = av;

	signal(CTRL_C, ft_sighandler);
	signal(CTRL_D, ft_sighandler);
	signal(CTRL_BS, ft_sighandler);

	vars = NULL;
	ft_clone_env(&vars, env);

	//---------------------------------
	//lista di variabili aggiuntive (provvisoria)
	ft_vars_ex(&vars);
	//---------------------------------
	
	while (1)
	{
		cmd = NULL;
		str = readline("$>");
		if (!ft_check_cmd_err(str))
		{
			ft_parsing(&cmd, str, &vars);
			add_history(str);
			free(str);
			//---------------------------------
			//stampa di controllo del parsing
			//(da rimuovere)
			ft_print_lst(cmd);
			//---------------------------------

			ft_pipes(&cmd, &vars, 1);
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
