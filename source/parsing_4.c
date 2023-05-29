/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:27:35 by abettini          #+#    #+#             */
/*   Updated: 2023/05/29 18:09:24 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//calcola la lunghezza del nome della variabile
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

//------------------------------------------------------------------------------
//calcola la lunghezza di line
//considerando il contenuto delle variabili
static int	ft_var_cont_len(char *str, char **env, t_list **vars)
{
	char	*var_name;
	int		len;

	var_name = ft_substr(str, 0, ft_var_name_len(str));
	len = ft_strlen(ft_find_var(var_name, env, vars));
	free(var_name);
	return (len);
}

int	ft_quotes_vars_len(char *str, char **env, t_list **vars)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else if (str[i] == '\'')
		{
			len += ft_char_char_len(&str[i], '\'') - 2;
			i += ft_char_char_len(&str[i], '\'');
		}
		else if (str[i] == '$')
		{
			len += ft_var_cont_len(&str[i + 1], env, vars);
			i += 1 + ft_var_name_len(&str[i + 1]);
		}
		else if (++i)
			len++;
	}
	return (len);
}

//------------------------------------------------------------------------------
//copia il contenuto delle variabili dentro line
//(solo se non all'interno di single quotes)
//e copia tutto il resto sempre dentro line
static int	ft_var_cpy(char *line, char *str, char **env, t_list **vars)
{
	char	*var_name;
	char	*var_cont;
	int		var_len;

	var_name = ft_substr(str, 0, ft_var_name_len(str));
	var_cont = ft_find_var(var_name, env, vars);
	free(var_name);
	var_len = ft_strlen(var_cont);
	ft_strlcpy(line, var_cont, var_len + 1);
	return (var_len);
}

void	ft_quotes_vars_cpy(char *line, char *str, char **env, t_list **vars)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				line[len++] = str[i++];
			if (str[i])
				i++;
		}
		else if (str[i] == '$')
		{
			len += ft_var_cpy(&line[len], &str[i + 1], env, vars);
			i += 1 + ft_var_name_len(&str[i + 1]);
		}
		else
			line[len++] = str[i++];
	}
}
