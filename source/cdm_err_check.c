/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdm_err_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:10:50 by abettini          #+#    #+#             */
/*   Updated: 2023/05/29 12:21:28 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_max_consec_char(char *str, char c)
{
	int	i;
	int	count_max;
	int	count_tmp;

	count_max = 0;
	count_tmp = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count_tmp++;
		else
		{
			if (count_tmp > count_max)
				count_max = count_tmp;
			count_tmp = 0;
		}
		i++;
	}
	if (count_tmp > count_max)
		count_max = count_tmp;
	return (count_max);
}

int	ft_check_weird(char *str)
{
	int		i;
	int		check;
	char	tmp;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && !(str[i] == '>' || str[i] == '<'))
			check = 0;
		if ((str[i] == '>' || str[i] == '<') && check != 0)
		{
			if (str[i] != tmp)
				return (1);
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			tmp = str[i];
			check = 1;
		}
		i++;
	}
	return (0);
}

int	ft_check_weird_2(char *str, char c)
{
	int		i;
	int		check;
	char	tmp;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != c)
			check = 0;
		if (str[i] == c && check != 0)
			return (1);
		else if (str[i] == c)
			check = 1;
		i++;
	}
	if (check)
		return (1);
	return (0);
}

int	ft_check_weird_3(char *str, char c)
{
	int		i;
	int		check;
	char	tmp;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			while (ft_isspace(str[i]))
				i++;
			if (!str[i] || ft_is_special(str[i]))
				return (1);
		}
		else
			i++;
	}
	return (0);
}


int	ft_check_cmd_err(char *str)
{
	if (ft_max_consec_char(str, '|') > 1)
		return (printf("syntax error\n") * 0 + 1);
	if (ft_max_consec_char(str, '>') > 2)
		return (printf("syntax error\n") * 0 + 1);
	if (ft_max_consec_char(str, '<') > 2)
		return (printf("syntax error\n") * 0 + 1);
	if (ft_check_weird(str))
		return (printf("syntax error\n") * 0 + 1);
	if (ft_check_weird_2(str, '|'))
		return (printf("syntax error\n") * 0 + 1);
	if (ft_check_weird_3(str, '>'))
		return (printf("syntax error\n") * 0 + 1);
	if (ft_check_weird_3(str, '<'))
		return (printf("syntax error\n") * 0 + 1);
	return (0);
}
