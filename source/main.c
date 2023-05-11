/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/05/11 12:46:37 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_lst(t_list *lst)
{
	t_prs *tmp;
	int		i;

	while (lst)
	{
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
	}
}

int	main(void)
{
	char	*str;
	t_list	*cmd;

	while (1)
	{
		ft_putstr_fd("$>", 1);
		str = readline(0);
		cmd = ft_parsing(str);
		ft_print_lst(cmd);
		add_history(str);
		free(str);
	}
	return (0);
}