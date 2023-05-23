/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:44:04 by abettini          #+#    #+#             */
/*   Updated: 2023/05/23 11:57:27 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_quotes_len(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		if (str[i])
			i++;
	}
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"' && str[i])
			i++;
		if (str[i])
			i++;
	}
	return (i);
}

//calcola la lunghezza del redirect
int	ft_red_len(char *str)
{
	int		i;
	bool	end;

	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (ft_isspace(str[i]))
		i++;
	end = 0;
	while (!end)
	{
		i += ft_quotes_len(&str[i]);
		if (!str[i] || ft_is_special(str[i]) || ft_isspace(str[i]))
			end = 1;
		else
			i++;
	}
	//printf ("redlen = %d\n", i);
	return (i);
}

//calcola la lunghezza della parola
int	ft_wrd_len(char *str)
{
	int		i;
	bool	end;

	i = 0;
	end = 0;
	while (!end)
	{
		i += ft_quotes_len(&str[i]);
		if (!str[i] || ft_is_special(str[i]) || ft_isspace(str[i]))
			end = 1;
		else
			i++;
	}
	//printf ("wrdlen = %d\n", i);
	return (i);
}

//conta quanti redirect ci sono
int	ft_red_count(char *str)
{
	int	i;
	int	red_count;

	red_count = 0;
	i = 0;
	while (str[i] != '|' && str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '>' || str[i] == '<')
		{
			red_count += 1;
			i += ft_red_len(&str[i]);
		}
		else
			i += ft_wrd_len(&str[i]);
	}
	//printf ("rec count = %d\n", red_count);
	return (red_count);
}

//conta quante parole ci sono
int	ft_wrd_count(char *str)
{
	int	i;
	int	wrd_count;

	wrd_count = 0;
	i = 0;
	while (str[i] != '|' && str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '>' || str[i] == '<')
			i += ft_red_len(&str[i]);
		else
		{
			wrd_count += 1;
			i += ft_wrd_len(&(str[i]));
		}
	}
	//printf ("wrd count = %d\n", wrd_count);
	return (wrd_count);
}
