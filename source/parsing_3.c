/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:01:18 by abettini          #+#    #+#             */
/*   Updated: 2023/05/30 15:58:05 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FT_GET_VAR_CONT---------------------------------------------------------------
//cerca variabile:
// - nella lista di vars
//restituisce:
// - stringa dopo l'uguale (=), oppure
// - "\0" se non la trova
char	*ft_get_var_cont(char *var_name, t_list **vars)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	tmp = *vars;
	while (tmp && !(!ft_strncmp(var_name, ((t_var *)tmp->content)->str, len) \
		&& ((t_var *)tmp->content)->str[len] == '='))
		tmp = tmp->next;
	if (tmp)
		return (((t_var *)tmp->content)->str + len + 1);
	return ("\0");
}

//FT_QUOTES_VARS---------------------------------------------------------------
//- calcola lenght del content della variabile
//- alloca memoria
//- copia content dalla variabile in nuova stringa
char	*ft_quotes_vars(char *str, t_list **vars)
{
	int		len;
	char	*line;

	len = ft_quotes_vars_len(str, vars);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	ft_quotes_vars_cpy(line, str, vars);
	free(str);
	return (line);
}
//----------------------------------------------------------------------------

void	ft_check_expand(t_list **lst, t_list **vars)
{
	t_prs	*tmp;
	t_list	*scr;
	int		y;

	scr = *lst;
	while (scr)
	{
		tmp = (t_prs *)scr->content;
		y = 0;
		while (tmp->wrd[y])
		{
			tmp->wrd[y] = ft_quotes_vars(tmp->wrd[y], vars);
			y++;
		}
		y = 0;
		while (tmp->red[y])
		{
			tmp->red[y] = ft_quotes_vars(tmp->red[y], vars);
			y++;
		}
		scr = scr->next;
	}
}
