/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:01:18 by abettini          #+#    #+#             */
/*   Updated: 2023/06/29 14:17:46 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FT_GET_VAR_CONT---------------------------------------------------------------
//looks for the variable:
// - in the vars list
//returns:
// - the string after the equal sign (=), or
// - "\0" if it doesn't find it
char	*ft_get_var_cont(char *var_name, t_list **vars)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	tmp = *vars;
	while (tmp && ft_strncmp(var_name, ((t_var *)tmp->content)->name, len + 1))
		tmp = tmp->next;
	if (tmp)
		return (((t_var *)tmp->content)->value);
	return ("\0");
}

//FT_QUOTES_VARS---------------------------------------------------------------
//- measure the lenght of the content of the variable
//- allocate memory
//- copies content of the variable in a new string
char	*ft_quotes_vars(char *str, t_msh *msh)
{
	int		len;
	char	*line;

	len = ft_quotes_vars_len(str, msh);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	ft_quotes_vars_cpy(line, str, msh);
	free(str);
	return (line);
}
//----------------------------------------------------------------------------

void	ft_check_expand(t_msh *msh)
{
	t_prs	*tmp;
	t_list	*scr;
	int		y;

	scr = *(msh->cmd);
	while (scr)
	{
		tmp = (t_prs *)scr->content;
		y = 0;
		while (tmp->wrd[y])
		{
			tmp->wrd[y] = ft_quotes_vars(tmp->wrd[y], msh);
			y++;
		}
		y = 0;
		while (tmp->red[y])
		{
			tmp->red[y] = ft_quotes_vars(tmp->red[y], msh);
			y++;
		}
		scr = scr->next;
	}
}
