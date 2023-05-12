/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:44:04 by abettini          #+#    #+#             */
/*   Updated: 2023/05/12 12:40:28 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//conta quanto e' lungo il redirect
//(lo uso per portare l'indice oltre il redirect)
static int	ft_skip_red(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (ft_isspace(str[i]))
		i++;
	while (!ft_is_special(str[i]) && !ft_isspace(str[i]) && str[i])
		i++;
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
			i += ft_skip_red(&str[i]);
		}
		else
			i++;
	}
	return (red_count);
}

//conta quante parole (che non siano redirect) ci sono
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
			i += ft_skip_red(&str[i]);
		else
		{
			wrd_count += 1;
			while (!ft_is_special(str[i]) && !ft_isspace(str[i]) && str[i])
				i++;
		}
	}
	return (wrd_count);
}
