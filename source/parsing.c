/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:03:09 by abettini          #+#    #+#             */
/*   Updated: 2023/05/11 12:57:51 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//conta quante parole e quanti redirect ci sono
static void	ft_prs_count(char *str, int *wc, int *rc)
{
	int	i;

	*rc = 0;
	*wc = 0;
	i = 0;
	while (str[i] != '|' && str[i])
	{
		while (ft_isspace(str[i]))
				i++;
		if (str[i] == '>' || str[i] == '<')
		{
			*rc += 1;
			while (str[i] == '>' || str[i] == '<')
				i++;
			while (ft_isspace(str[i]))
				i++;
			while (!ft_is_special(str[i]) && !ft_isspace(str[i]) && str[i])
				i++;
		}
		else if (str[i])
		{
			*wc += 1;
			while (!ft_is_special(str[i]) && !ft_isspace(str[i]) && str[i])
				i++;
		}
	}
	printf ("word count = %d\nredirect count = %d\n", *wc, *rc);
}

int		ft_strlenmod(char *str, int red)
{
	int	i;

	i = 0;
	if (red == 1)
	{
		while (str[i] == '>' || str[i] == '<')
			i++;
		if (ft_isspace(str[i]))
		{
			while (ft_isspace(str[i]))
				i++;
		}
	}
	while (!ft_is_special(str[i]) && str[i])
		i++;
	return (i);
}

//crea una lista di nodi dividendo parole e redirect
t_list	*ft_parsing(char *str)
{
	t_list	*lst;
	t_prs	*tmp;
	int		i;
	int		wc;
	int		rc;
	int		r;
	int		w;

	lst = NULL;
	r = 0;
	w = 0;
	i = 0;
	while (str[i])
	{
		tmp = malloc(sizeof(t_prs));
		if (!lst)
			lst = ft_lstnew((void *)tmp);
		else
			ft_lstadd_front(&lst, ft_lstnew((void *)tmp));
		ft_prs_count(&str[i], &wc, &rc);
		tmp->wrd = malloc(sizeof(char *) * wc);
		tmp->red = malloc(sizeof(char *) * rc);
		while (str[i] != '|' && str[i])
		{
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '>' || str[i] == '<')
			{
				tmp->red[r] = malloc(ft_strlenmod(&str[i], 1) + 1);
				ft_strlcpy(tmp->red[r], &str[i], ft_strlenmod(&str[i], 1) + 1);
				i += ft_strlenmod(&str[i], 1);
				r++;
			}
			else
			{
				tmp->wrd[w] = malloc(ft_strlenmod(&str[i], 0) + 1);
				ft_strlcpy(tmp->wrd[w], &str[i], ft_strlenmod(&str[i], 0) + 1);
				i += ft_strlenmod(&str[i], 0);
				w++;
			}
		}
	}
	return (lst);
}