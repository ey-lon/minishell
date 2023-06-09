/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:36:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/09 10:19:24 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **mat, int fd, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (mat[i])
	{
		j = 0;
		while (mat[i][j])
		{
			write(fd, &mat[i][j], 1);
			j++;
		}
		i++;
		if (mat[i])
			write(fd, " ", 1);
	}
	if (!flag)
		write(fd, "\n", 1);
}
