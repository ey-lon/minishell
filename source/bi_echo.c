/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:36:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/20 11:25:33 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int		i;
	int		j;
	bool	flag;

	flag = 0;
	if (*args && !ft_strncmp(*args, "-n", 3))
	{
		flag = 1;
		args++;
	}
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			write(STDOUT_FILENO, &args[i][j], 1);
			j++;
		}
		i++;
		if (args[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
}
