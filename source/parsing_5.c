/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:37:38 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 11:22:03 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

int	ft_var_name_len(char *str);

//FT_QUOTES_VARS_CPY------------------------------------------------------------
//copies the content of the variables into line
//(only if not inside single quotes)
//and copies all the rest into line
static int	ft_var_cpy(char *line, char *str, t_msh *msh)
{
	char	*var_name;
	char	*var_cont;
	int		var_len;

	if (!*str || (*str != '?' && !ft_isalnum(*str)))
		var_len = ft_strlcpy(line, "$", 2);
	else if (*str == '?')
	{
		var_cont = ft_itoa(g_exit_code);
		var_len = ft_strlen(var_cont);
		ft_strlcpy(line, var_cont, var_len + 1);
		free(var_cont);
	}
	else
	{
		var_name = ft_substr(str, 0, ft_var_name_len(str));
		var_cont = ft_get_var_cont(var_name, msh->vars);
		free(var_name);
		var_len = ft_strlen(var_cont);
		ft_strlcpy(line, var_cont, var_len + 1);
	}
	return (var_len);
}

int	ft_stat_cpy(int check, int *stat, char c, char *dest)
{
	if (!*stat || *stat == check)
		*stat = check - *stat;
	else
	{
		*dest = c;
		return (1);
	}
	return (0); 
}

void	ft_quotes_vars_cpy(char *line, char *str, t_msh *msh)
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
			len += ft_stat_cpy(2, &stat, '\"', &(line[len]));
		else if (str[i] == '\'' && ++i)
			len += ft_stat_cpy(1, &stat, '\'', &(line[len]));
		else if (str[i] == '$' && stat != 1)
		{
			len += ft_var_cpy(&line[len], &str[i + 1], msh);
			i += 1 + ft_var_name_len(&str[i + 1]);
		}
		else
			line[len++] = str[i++];
	}
}
