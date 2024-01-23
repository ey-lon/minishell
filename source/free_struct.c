/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:23:05 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 14:59:22 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free t_var--------------------------------------------------------------------
void	ft_free_varsnode(void *vars)
{
	t_var	*tmp;

	tmp = (t_var *)(vars);
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

/*
//[depracated]
void	ft_free_varslst(t_list **lst)
{
	ft_lstclear(lst, ft_free_varsnode);
}
*/

//free t_prs--------------------------------------------------------------------
void	ft_free_cmdnode(void *vars)
{
	t_prs	*tmp;

	tmp = (t_prs *)(vars);
	ft_free_mat(tmp->wrd);
	ft_free_mat(tmp->red);
	free(tmp);
}

/*
//[depracated]
void	ft_free_cmdlst(t_list **lst)
{
	ft_lstclear(lst, ft_free_cmdnode);

}
*/