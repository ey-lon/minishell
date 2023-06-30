/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:23:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/30 12:07:16 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_msh *msh, char **args)
{
	unsigned char	ret;

	ret = 0;
	if (!(*(msh->cmd))->next)
	{
		if (args[0] && args[1])
		{
			ret = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else
		{
			msh->exit = 1;
			if (*args)
				ret = ft_atoi(*args) % 256;
		}
	}
	return (ret);
}
