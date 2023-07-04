/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:36:28 by abettini          #+#    #+#             */
/*   Updated: 2023/07/04 10:00:45 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	flag = 0;
	if (*args && !ft_strncmp(*args, "-n", 3))
		flag = ++i;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			write(1, &args[i][j], 1);
			j++;
		}
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}
