/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:10:37 by abettini          #+#    #+#             */
/*   Updated: 2023/06/09 15:21:25 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_node(t_list *vars)
{
	t_var	*tmp;

	tmp = (t_var *)vars;
	free(tmp->name);
	free(tmp->value);
	free(vars);
}

void	ft_unset(t_list **vars, char *var_name)
{
	t_list	*scr;
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	scr = *vars;
	if (scr && !ft_strncmp(var_name, ((t_var *)scr->content)->name, len + 1))
	{
		*vars = scr->next;
		ft_free_node(scr);
	}
	else
	{
		while (scr && scr->next \
			&& ft_strncmp(var_name, \
			((t_var *)scr->next->content)->name, len + 1))
			scr = scr->next;
		if (scr && scr->next)
		{
			tmp = scr->next->next;
			ft_free_node(scr->next);
			scr->next = tmp;
		}
	}
}
