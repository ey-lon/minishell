/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/05/31 14:33:01 by abettini         ###   ########.fr       */
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

void	ft_free_cmdlst(t_list *lst)
{
	t_prs	*tmp;

	if (lst)
	{
		ft_free_cmdlst(lst->next);
		tmp = (t_prs *)lst->content;
		ft_free_mat(tmp->wrd);
		ft_free_mat(tmp->red);
		free(tmp);
		free(lst);
	}
}

//-------------------------------------------------------
//funzione per creare dei nodi nella lista di variabili
//(usata per testare)
void	ft_vars_ex(t_list **vars)
{
	t_var	*new;

	new = malloc(sizeof(t_var) * 1);
	new->str = ft_strdup("VAR1=cho");
	new->exp = false;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
	new = malloc(sizeof(t_var) * 1);
	new->str = ft_strdup("VAR2=banana");
	new->exp = true;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
	new = malloc(sizeof(t_var) * 1);
	new->str = ft_strdup("VAR11=test");
	new->exp = false;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
}
//-------------------------------------------------------

void	ft_clone_env(t_list **vars, char **env)
{
	int		i;
	t_var	*new;

	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(t_var));
		new->str = ft_strdup(env[i]);
		new->exp = true;
		ft_lstadd_back(vars, ft_lstnew((void *)new));
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*cmd;
	t_list	*vars;

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
		if (!strncmp(str, "exit", 4))
			break ;
		if (!ft_check_cmd_err(str))
		{
			ft_parsing(&cmd, str, &vars);

			//---------------------------------
			//stampa di controllo del parsing
			//(da rimuovere)
			ft_print_lst(cmd);
			//---------------------------------

			//---------------------------------
			//qui vanno eseguiti i comandi
			//ft_exec_cmd(cmd, my env, vars)???
			//---------------------------------
			//ft_lstclear(&cmd, free);
			ft_free_cmdlst(cmd);
		}
		add_history(str);
		free(str);
	}

	//---------------------------------
	//libero in caso si digiti exit
	//(soluzione provvisoria)
	free(str);
	//ft_lstclear(&vars, free);
	ft_free_varslst(&vars);
	//---------------------------------
	
	return (0);
}
