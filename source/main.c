/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/05/26 12:15:30 by abettini         ###   ########.fr       */
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
		ft_putstr_fd("\n$> ", 1);
}

/* stampa la lista di nodi
contentente le matrici di parole e redirects
(funzione usata solo per vedere se sono linkati per bene) */
void	ft_print_lst(t_list *lst)
{
	t_prs	*tmp;
	int		i;
	int		n;

	n = 1;
	printf("\n");
	while (lst)
	{
		printf("NODE [%d]\n", n);
		tmp = (t_prs *)lst->content;
		printf("___words:_______\n");
		i = 0;
		while (tmp->wrd[i])
		{
			printf("%s\n", tmp->wrd[i]);
			i++;
		}
		printf("___redirects:___\n");
		i = 0;
		while (tmp->red[i])
		{
			printf("%s\n", tmp->red[i]);
			i++;
		}
		lst = lst->next;
		n++;
	}
	printf("\n");
}

void	ft_free_cmdlst(t_list *lst)
{
	t_prs	*tmp;

	if (lst)
	{
		tmp = (t_prs *)lst->content;
		ft_free_cmdlst(lst->next);
		ft_free_mat(tmp->wrd);
		ft_free_mat(tmp->red);
		free(tmp);
		free(lst);
	}
}

void	ft_vars_ex(t_list **vars)
{
	t_var	*new;

	new = malloc(sizeof(t_var) * 1);
	new->str = ft_strdup("VAR1=cho");
	ft_lstadd_front(vars, ft_lstnew((void *)new));
	new = malloc(sizeof(t_var) * 1);
	new->str = ft_strdup("VAR2=banana");
	ft_lstadd_front(vars, ft_lstnew((void *)new));
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*cmd;

	//char	**env;
	t_list	*vars;

	signal(CTRL_C, ft_sighandler);
	signal(CTRL_D, ft_sighandler);
	signal(CTRL_BS, ft_sighandler);

	vars = NULL;
	ft_vars_ex(&vars);

	while (1)
	{
		cmd = NULL;
		str = readline("$> ");
		if (!strncmp(str, "exit", 4))
			exit (0);
		if (!ft_check_cmd_err(str))
		{
			ft_parsing(&cmd, str, env, &vars);
			ft_print_lst(cmd);
			//execute cmd
			ft_free_cmdlst(cmd);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
