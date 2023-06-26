/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:23:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/26 15:11:39 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!(*(msh->cmd))->next)
	{
		ret = 1;
	}
	ft_free_varslst(msh->vars);
	ft_free_cmdlst(msh->cmd);
	return (ret);
}
