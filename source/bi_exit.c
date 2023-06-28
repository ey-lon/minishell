/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:23:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/26 16:12:43 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_msh *msh, char **args)
{
	int	ret;

	ret = 0;
	if (!(*(msh->cmd))->next)
	{
		if (args[0] && args[1])
			ft_putstr_fd("exit: too many arguments\n", 2);
		else if (*args)
			ret = ft_atoi(*args);
		else
			ret = 1; 
	}
	return (ret);
}
