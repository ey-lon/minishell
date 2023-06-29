/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:27:35 by abettini          #+#    #+#             */
/*   Updated: 2023/06/29 11:43:33 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//measure the lenght of the name of the variable
int	ft_var_name_len(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]))
	{
		i++;
		while (ft_isalnum(str[i]))
			i++;
	}
	return (i);
}

//FT_QUOTES_VARS_LEN------------------------------------------------------------
//calculate the leanght of line
//considering the content of the variables
static int	ft_var_cont_len(char *str, t_list **vars)
{
	char	*var_name;
	int		len;

	var_name = ft_substr(str, 0, ft_var_name_len(str));
	len = ft_strlen(ft_get_var_cont(var_name, vars));
	free(var_name);
	return (len);
}

static int	ft_stat_len(int check, int *stat)
{
	if (!*stat || *stat == check)
		*stat = check - *stat;
	else
		return (1);
	return (0);
}

int	ft_quotes_vars_len(char *str, t_list **vars)
{
	int		i;
	int		len;
	int		stat;

	stat = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"' && ++i)
			len += ft_stat_len(2, &stat);
		else if (str[i] == '\'' && ++i)
			len += ft_stat_len(1, &stat);
		else if (str[i] == '$' && stat != 1)
		{
			len += ft_var_cont_len(&str[i + 1], vars);
			i += 1 + ft_var_name_len(&str[i + 1]);
		}
		else if (++i)
			len++;
	}
	return (len);
}
