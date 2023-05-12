/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/05/12 12:37:50 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sighandler(int signal)
{
	if (signal == SIGQUIT)
		;
	else if (signal == SIGSEGV)
	{
		ft_putstr_fd("exit", 1);
		exit(0);
	}
	else if (signal == SIGINT)
		ft_putstr_fd("\n$>", 1);
}

void	ft_print_lst(t_list *lst)
{
	t_prs	*tmp;
	int		i;
	int		n;

	n = 1;
	while (lst)
	{
		printf("\nnodo [%d]\n", n);
		tmp = (t_prs *)lst->content;
		printf("words:\n");
		i = 0;
		while (tmp->wrd[i])
		{
			printf("%s\n", tmp->wrd[i]);
			i++;
		}
		printf("redirects:\n");
		i = 0;
		while (tmp->red[i])
		{
			printf("%s\n", tmp->red[i]);
			i++;
		}
		lst = lst->next;
		n++;
	}
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

int	main(void)
{
	char	*str;
	t_list	*cmd;

	signal(SIGINT, ft_sighandler);
	signal(SIGSEGV, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	while (1)
	{
		cmd = NULL;
		str = readline("$> ");
		if (!strncmp(str, "exit", 4))
			exit (0);
		ft_parsing(&cmd, str);
		//ft_print_lst(cmd);
		//execute
		//add_history(str);
		free(str);
		ft_free_cmdlst(cmd);
	}
	return (0);
}
