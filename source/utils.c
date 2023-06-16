/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:03:28 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 10:22:51 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_special(char c)
{
	const char	*str;
	int			i;

	str = "|><";
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	ft_free_mat(char **mat)
{
	int	y;

	if (mat)
	{
		y = 0;
		while (mat[y])
		{
			free(mat[y]);
			y++;
		}
		free(mat);
	}
}
