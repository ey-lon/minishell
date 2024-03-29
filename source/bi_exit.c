/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:23:28 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 16:21:11 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	ft_digit_check(char *str)
{
	int	i;
	int	check;

	check = 0;
	if (str)
	{
		i = 0;
		if (str[i] == '-' || str[i] == '+' || ft_isdigit(str[i]))
			i++;
		else
			return (1);
		while (!check && str[i])
		{
			if (!ft_isdigit(str[i]))
				check = 1;
			i++;
		}
	}
	return (check);
}

int	ft_exit(t_msh *msh, char **args)
{
	unsigned char	ret;

	if (!(*(msh->cmd))->next)
		msh->exit = 1;
	if (!args[0])
		ret = g_exit_code;
	else if (args[0] && (ft_digit_check(*args) || ft_llong_limit_check(*args)))
	{
		ret = 2;
		ft_dprintf(2, \
			"minishell: exit: %s: numeric argument required\n", *args);
	}
	else if (args[0] && args[1])
	{
		msh->exit = 0;
		ret = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else
		ret = ft_atoi(*args) % 256;
	return (ret);
}
