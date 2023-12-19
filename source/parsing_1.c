/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:03:09 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 12:30:26 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//removes unnecessary spaces in the redirects
static char	*ft_red_trim(char *str, int *ind)
{
	char	*tmp;
	int		len;
	int		i;
	int		x;

	len = ft_red_len(str);
	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	x = i;
	while (ft_isspace(str[i]))
		i++;
	tmp = malloc(len - (i - x) + 1);
	i = 0;
	while (str[i] == '>' || str[i] == '<')
	{
		tmp[i] = str[i];
		i++;
	}
	x = i;
	while (ft_isspace(str[i]))
		i++;
	ft_strlcpy(&tmp[x], &str[i], ft_wrd_len(&str[i]) + 1);
	*ind += len;
	return (tmp);
}

static char	*ft_wrd_trim(char *str, int *ind)
{
	int		len;
	char	*tmp;

	len = ft_wrd_len(str);
	tmp = malloc(len + 1);
	ft_strlcpy(tmp, str, len + 1);
	*ind += len;
	return (tmp);
}

//fills the words matrix and the redirects matrix inside the node
static int	ft_fill_cmdlst(t_prs *tmp, char *str, int i)
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
			tmp->red[r] = ft_red_trim(&(str[i]), &i);
			r++;
		}
		else if (str[i] != '|')
		{
			tmp->wrd[w] = ft_wrd_trim(&(str[i]), &i);
			w++;
		}
	}
	return (i);
}

/*
creates a list of nodes containing:
- a matrix of words
- a matrix of redirects
(one node per pipe)
*/
static void	ft_first_split(t_list **lst, char *str)
{
	t_prs	*tmp;
	int		i;
	int		wc;
	int		rc;

	i = 0;
	while (str[i])
	{
		tmp = malloc(sizeof(t_prs));
		ft_lstadd_back(lst, ft_lstnew((void *)tmp));
		rc = ft_red_count(&str[i]);
		wc = ft_wrd_count(&str[i]);
		tmp->wrd = malloc(sizeof(char *) * (wc + 1));
		tmp->red = malloc(sizeof(char *) * (rc + 1));
		tmp->wrd[wc] = NULL;
		tmp->red[rc] = NULL;
		i = ft_fill_cmdlst(tmp, str, i);
		while (ft_isspace(str[i]) || str[i] == '|')
			i++;
	}
}

void	ft_parsing(char *str, t_msh *msh)
{
	ft_first_split(msh->cmd, str);
	ft_check_expand(msh);
}
