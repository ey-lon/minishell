/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:23 by abettini          #+#    #+#             */
/*   Updated: 2023/06/09 10:10:55 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_chars(char *str, char *c, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && i < n)
	{
		if (ft_strchr(c, str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_rm_chars(char *str, char *rm, int len)
{
	char	*ret;
	int		i;
	int		x;

	ret = malloc(sizeof(char) * (len - ft_count_chars(str, rm, len) + 1));
	x = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(rm, str[i]))
		{
			ret[x] = str[i];
			x++;
		}
		i++;
	}
	ret[x] = '\0';
	return (ret);
}

int	ft_strlen_mod(char *str, char end)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != end)
		i++;
	return (i);
}
