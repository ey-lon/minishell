/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:13:04 by abettini          #+#    #+#             */
/*   Updated: 2023/05/30 18:06:58 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the node list
containing the words and redirects matrixes
(function used to see if the parsing is correct) */
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
		printf("___words:_________\n");
		i = -1;
		while (tmp->wrd[++i])
			printf("%s\n", tmp->wrd[i]);
		printf("___redirects:_____\n");
		i = -1;
		while (tmp->red[++i])
			printf("%s\n", tmp->red[i]);
		printf("__________________\n\n");
		lst = lst->next;
		n++;
	}
}
