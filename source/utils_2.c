/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:23 by abettini          #+#    #+#             */
/*   Updated: 2023/07/19 11:03:49 by abettini         ###   ########.fr       */
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
	if (str)
	{
		while (str[i] && str[i] != end)
			i++;
	}
	return (i);
}

//FT_LLONG_LIMIT_CHECK-------------------------------------
static int	ft_llong_limit_ret(char *str)
{
	int			i;
	long long	res;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && i < 18)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_llong_limit_check(char *str)
{
	long long	res;
	int			sign;
	int			i;

	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(&str[i]) < 19)
		return (0);
	else if (ft_strlen(&str[i]) > 19)
		return (1);
	res = ft_llong_limit_ret(&str[i]);
	if (res > LLONG_MAX / 10)
		return (1);
	else if ((sign == 1 && str[i + 18] - '0' < 8) \
		|| (sign == -1 && str[i + 18] - '0' <= 8))
		return (0);
	return (1);
}
