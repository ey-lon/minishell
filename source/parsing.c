/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:03:09 by abettini          #+#    #+#             */
/*   Updated: 2023/05/12 12:37:34 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_count(char *str);
int	ft_wrd_count(char *str);

static int	ft_strlenmod(char *str, int red)
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
	while (!ft_is_special(str[i]) && !ft_isspace(str[i]) && str[i])
		i++;
	return (i);
}

char	*ft_red_trim(char *str)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = malloc(ft_strlenmod(str, 1) + 1);
	ft_strlcpy(tmp, str, ft_strlenmod(str, 1) + 1);
	while (tmp[i] == '>' || tmp[i] == '<')
		i++;
	while (ft_isspace(tmp[i]))
	{
		i++;
		x++;
	}
	while (tmp[i])
		i++;
	ret = malloc(sizeof(char) * (i - x + 1));
	i = 0;
	x = 0;
	while (tmp[i] == '>' || tmp[i] == '<')
	{
		ret[x] = tmp[i];
		i++;
		x++;
	}
	while (ft_isspace(tmp[i]))
		i++;
	while (tmp[i])
	{
		ret[x] = tmp[i];
		i++;
		x++;
	}
	ret[x] = '\0';
	free(tmp);
	return (ret);
}

int	ft_fill_cmdlst(t_prs *tmp, char *str, int i)
{
	int		r;
	int		w;

	r = 0;
	w = 0;
	while (str[i] != '|' && str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '>' || str[i] == '<')
		{
			tmp->red[r] = ft_red_trim(&str[i]);
			i += ft_strlenmod(&str[i], 1);
			r++;
		}
		else if (str[i] != '|')
		{
			tmp->wrd[w] = malloc(ft_strlenmod(&str[i], 0) + 1);
			ft_strlcpy(tmp->wrd[w], &str[i], ft_strlenmod(&str[i], 0) + 1);
			i += ft_strlenmod(&str[i], 0);
			w++;
		}
	}
	return (i);
}

//crea una lista di nodi contenenti:
//una matrice di parole e una di redirect
//per ogni pipe

void	ft_parsing(t_list **lst, char *str)
{
	t_prs	*tmp;
	int		i;
	int		wc;
	int		rc;

	i = 0;
	while (str[i])
	{
		tmp = malloc(sizeof(t_prs));
		ft_lstadd_front(lst, ft_lstnew((void *)tmp));
		rc = ft_red_count(&str[i]);
		wc = ft_wrd_count(&str[i]);
		tmp->wrd = malloc(sizeof(char *) * (wc + 1));
		tmp->red = malloc(sizeof(char *) * (rc + 1));
		tmp->wrd[wc] = NULL;
		tmp->red[rc] = NULL;
		i = ft_fill_cmdlst(tmp, str, i);
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			i++;
	}
}
