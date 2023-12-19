/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:38:34 by abettini          #+#    #+#             */
/*   Updated: 2023/05/12 09:54:05 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_str_to_history(char *str, t_list **hst)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(hst, new);
	return (0);
}

int	ft_print_history(t_list *hst)
{
	int	i;

	i = 1;
	while (hst)
	{
		printf("%5d  %s\n", i, (char *)hst->content);
		hst = hst->next;
		i++;
	}
	return (0);
}
