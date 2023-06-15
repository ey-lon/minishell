/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:23:05 by abettini          #+#    #+#             */
/*   Updated: 2023/06/15 14:48:22 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free t_var--------------------------------------------------------------------
void	ft_free_varsnode(t_list *vars)
{
	t_var	*tmp;

	tmp = (t_var *)(vars->content);
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	free(vars);
}

void	ft_free_varslst(t_list **lst)
{
	if (lst && *lst)
	{
		ft_free_varslst(&(*lst)->next);
		ft_free_varsnode(*lst);
	}
}

//free t_prs--------------------------------------------------------------------
void	ft_free_cmdnode(t_list *vars)
{
	t_prs	*tmp;

	tmp = (t_prs *)(vars->content);
	ft_free_mat(tmp->wrd);
	ft_free_mat(tmp->red);
	free(tmp);
	free(vars);
}

void	ft_free_cmdlst(t_list **lst)
{
	if (lst && *lst)
	{
		ft_free_cmdlst(&(*lst)->next);
		ft_free_cmdnode(*lst);
	}
}
