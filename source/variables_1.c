/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:52:07 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 10:24:38 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_variable_cmd(char *str)
{
	int	check;
	int	i;

	if (!ft_strchr(str, '='))
		return (0);
	check = 1;
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (str[i] != '=' && check == 1)
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			else
				check = 0;
		}
	}
	else
		check = 0;
	return (check);
}

int	ft_variable_cmd(t_list **vars, char *str)
{
	int	check;

	check = 0;
	if (ft_is_variable_cmd(str))
	{
		ft_handle_var_by_str(vars, str);
		check = 1;
	}
	return (check);
}
