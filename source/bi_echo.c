/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:36:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/13 12:05:27 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args, int flag)
{
	int	i;
	int	j;

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
