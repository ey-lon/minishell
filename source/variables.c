/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:32:12 by abettini          #+#    #+#             */
/*   Updated: 2023/05/31 14:30:37 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_var(t_list **vars, char *str)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return ;
	new->str = ft_strdup(str);
	new->exp = false;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
}

void	ft_free_varslst(t_list **lst)
{
	t_var	*tmp;

	if (lst && *lst)
	{
		ft_free_varslst(&(*lst)->next);
		tmp = (t_var *)(*lst)->content;
		free(tmp->str);
		free(tmp);
		free(*lst);
	}
}
